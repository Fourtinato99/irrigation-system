/*
 * Irrigation_system.c
 *
 * Created: 9/8/2022 10:59:46 PM
 * Author : effic
 */

#include "STD_MACROS.h"
#include "UTILITIES.h"
#include "I2C.h"
#include "LCD.h"

#include "SHIFT_REGISTER.h"
#include "TIMER1.h"
#include "INTERRUPT.h"
#include "DS1307.h"
#include <avr/interrupt.h>



volatile uint8 set_time_mode = 0;
volatile uint8 set_timers_mode;
volatile uint8 manual_mode = 0;

volatile uint8 DS_time[7] = { 0 };
volatile uint8 DS_time_temp[7] = { 0 };
// set timers variables

volatile timerUp timers ;

volatile uint8 time_mode_flag = 0;
volatile uint8 timer_flag;
volatile uint8 manual_flag = 0;



volatile uint8 display_timer_properties;
volatile uint8 selector = 0;
volatile uint8 OK = 0;
volatile uint8 running_timers = 0;
volatile uint8 date_counter = 0;
volatile uint8 timer_changer = 0;


volatile uint8 prev_second = 0;


int main(void)
{
	
	
	//////////////////////////////////////////////////////////////////////////
    /* Replace with your application code */
    //initiating LCD
    LCD_init_4();
	LCD_y_x(1,1);
	
	

	//////////////////////////////////////////////////////////////////////////
	
	
	

     //////////////////////////////////////////////////////////////////////////
    //initiating shift register 
    SHIFT_REGISTER_init();
	SHIFT_REGISTER_OUT(0);
	
	//////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////
	// intiating timer overflow
	TIMER1_init_normal(5);
	SET_BIT(DDRD,0);
	 
	//////////////////////////////////////////////////////////////////////////
	

		
	

    //////////////////////////////////////////////////////////////////////////
    //initiating I2C master
    I2C_master_init(50);
   // I2C_master_start();
   DS1307_read_time(DS_time);
   DS1307_save_time(DS_time);
   prev_second = DS_time[0];
	//////////////////////////////////////////////////////////////////////////
	
	
	
	
	



    //////////////////////////////////////////////////////////////////////////
    //initiating interrupt for buttons using pin change interrupt
     //1-set pins as input with pull up
   
	UTILITY_init_button();
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	// initiating some testing timing
	/*
	for(uint8 i=1 ; i<=24;i++)
	{
		timers.timer= 0x7fff00;
		timers.timer_properties.start_hours = i-1;
		timers.timer_properties.start_minutes = 0;
		timers.timer_properties.period_hours = i-1;
		timers.timer_properties.period_minutes = 10;
		EEPROM_write_64(i*8,timers.timer);
		
	}
	
		for(uint8 i=1 ; i<=24;i++)
		{
			timers.timer= 0x7fff00;
			timers.timer_properties.start_hours = i-1;
			timers.timer_properties.start_minutes = 15;
			timers.timer_properties.period_hours = i-1;
			timers.timer_properties.period_minutes = 30;
			EEPROM_write_64(25*8+i*8,timers.timer);
			
		}
		
		
				for(uint8 i=1 ; i<=24;i++)
				{
					timers.timer= 0x7fff00;
					timers.timer_properties.start_hours = i-1;
					timers.timer_properties.start_minutes = 35;
					timers.timer_properties.period_hours = i-1;
					timers.timer_properties.period_minutes = 55;
					EEPROM_write_64(50*8+i*8,timers.timer);
					
				}
	
	

  
    */
    //////////////////////////////////////////////////////////////////////////
    while (1)
    {


        //////////////////////////////////////////////////////////////////////////
		//set time mode
        if (1 == set_time_mode) 
        {

            UTILITY_display_time(DS_time_temp);

            if (1 == OK) // save time
            {
                set_time_mode = 0;
                OK = 0;
                DS1307_save_time(DS_time_temp);
            }

        }
		//////////////////////////////////////////////////////////////////////////
		
		
		
		//////////////////////////////////////////////////////////////////////////
		//set timers mode
        else if (1 == set_timers_mode) 
        {


            //////////////////////////////////////////////////////////////////////////
            //display properties only
            if (1 == display_timer_properties)
            {
				UTILITY_display_timer();
               
            }
            //////////////////////////////////////////////////////////////////////////
            //display to selector properties
            else
            {
                UTILITY_display_edit_timer();
	
            }

        }
		//////////////////////////////////////////////////////////////////////////
		
		
		
		
		//////////////////////////////////////////////////////////////////////////
		// manual mode
        else if (1 == manual_mode)    
        {
            UTILITY_display_manual(running_timers);

        }
		//////////////////////////////////////////////////////////////////////////
		
		
		
		
		//////////////////////////////////////////////////////////////////////////
		//        display time only
        else {


            DS1307_read_time(DS_time);
            UTILITY_display_time(DS_time);

        }
		//////////////////////////////////////////////////////////////////////////
		
		

        //////////////////////////////////////////////////////////////////////////
        //         turn on/off  relay
        SHIFT_REGISTER_OUT(running_timers);
		
        //////////////////////////////////////////////////////////////////////////


    }
}







ISR(PCINT1_vect)
{
    for (uint16 i = 0;i <= 65000 ;i++); //delay

    if (0 == READ_BIT(PINC, SET_TIME_BT)) //set time button isr
    {
        set_time_mode = set_time_mode == 0 ? 1 : 0;
        manual_mode = 0;
        manual_flag = 0;
		selector = 0;
        set_timers_mode = 0;
        time_mode_flag = 1;

        DS_time_temp[0] = DS_time[0];
        DS_time_temp[1] = DS_time[1];
        DS_time_temp[2] = DS_time[2];
        DS_time_temp[3] = DS_time[3];
        DS_time_temp[4] = DS_time[4];
        DS_time_temp[5] = DS_time[5];
        DS_time_temp[6] = DS_time[6];

        while (0 == READ_BIT(PINC, SET_TIME_BT));
    }
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    //        set timers button ISR

    if (0 == READ_BIT(PINC, SET_TIMER_BT))
    {
        set_time_mode = 0;
        manual_mode = 0;
        selector = 0;
        manual_flag = 0;
        time_mode_flag = 0;
		timers.timer = 0;
		timers.timer_properties.on_off=1;
		timer_changer = 0 ;


        timer_flag = 1;
        selector = 1;
        display_timer_properties = 1 ;
        set_timers_mode = set_timers_mode == 0 ? 1 : 0;
		


        while (0 == READ_BIT(PINC , SET_TIMER_BT));  //waiting until removing his fucking finger

    }
    //////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////
    //        manual button ISR

    if (0 == READ_BIT(PINC, MANUAL_BT))
    {
        set_time_mode = 0;
        set_timers_mode = 0;
        selector = 0;
        manual_mode = manual_mode == 0 ? 1 : 0;
        manual_flag = 1;

        while (0 == READ_BIT(PINC, MANUAL_BT));  //waiting until removing his fucking finger

    }
    //////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////
    //up button  isr
    if (0 == READ_BIT(PINC, UP_BT))
    {

        if (1 == set_timers_mode )
        {
			//////////////////////////////////////////////////////////////////////////
			//    controller of timer changer
			if(display_timer_properties == 1)
			{
				
				
				while(timer_changer <128)
				{
					if(0 == EEPROM_read_8((timer_changer)*8) && timer_changer != 0 )
					{
						timers.timer = EEPROM_read_64((timer_changer)*8)	;
						timer_changer++;
						break;
					}
					timer_changer++;
					
				}
					
					
				if(128 == timer_changer)
				{
					timer_changer = 0;
					timers.timer = 0;
					timers.timer_properties.on_off = 1;
				}
					
					
							
				
				
				
			}

            //////////////////////////////////////////////////////////////////////////
            //controller turn on / off
            else if (1 == selector)    timers.timer_properties.on_off = !timers.timer_properties.on_off;
            //////////////////////////////////////////////////////////////////////////


            //////////////////////////////////////////////////////////////////////////
            //controller days
            else if (2 == selector)    timers.timer_properties.day1 = !timers.timer_properties.day1;
            else if (3 == selector)    timers.timer_properties.day2 = !timers.timer_properties.day2;
            else if (4 == selector)    timers.timer_properties.day3 = !timers.timer_properties.day3;
            else if (5 == selector)    timers.timer_properties.day4 = !timers.timer_properties.day4;
            else if (6 == selector)    timers.timer_properties.day5 = !timers.timer_properties.day5;
            else if (7 == selector)    timers.timer_properties.day6 = !timers.timer_properties.day6;
            else if (8 == selector)    timers.timer_properties.day7 = !timers.timer_properties.day7;
            //////////////////////////////////////////////////////////////////////////


            //////////////////////////////////////////////////////////////////////////
            // controller  timers
            else if ( 9 == selector)    timers.timer_properties.timer1 = !timers.timer_properties.timer1;
            else if (10 == selector)    timers.timer_properties.timer2 = !timers.timer_properties.timer2;
            else if (11 == selector)    timers.timer_properties.timer3 = !timers.timer_properties.timer3;
            else if (12 == selector)    timers.timer_properties.timer4 = !timers.timer_properties.timer4;

            else if (13 == selector)    timers.timer_properties.timer5 = !timers.timer_properties.timer5;
            else if (14 == selector)    timers.timer_properties.timer6 = !timers.timer_properties.timer6;
            else if (15 == selector)    timers.timer_properties.timer7 = !timers.timer_properties.timer7;
            else if (16 == selector)    timers.timer_properties.timer8 = !timers.timer_properties.timer8;
            //////////////////////////////////////////////////////////////////////////




            //////////////////////////////////////////////////////////////////////////
            //control start time and period
            else if (17 == selector) (timers.timer_properties.start_hours++     , timers.timer_properties.start_hours    %=24);
            else if (18 == selector) ( timers.timer_properties.start_minutes++  , timers.timer_properties.start_minutes  %=60);
            else if (19 == selector) (timers.timer_properties.period_hours++    , timers.timer_properties.period_hours   %=24);
            else if (20 == selector) ( timers.timer_properties.period_minutes++ , timers.timer_properties.period_minutes %=60);
			
			
            //////////////////////////////////////////////////////////////////////////




        }
        else if (1 == set_time_mode)
        {
            //////////////////////////////////////////////////////////////////////////
            // controller of time
            DS_time_temp[selector]++;
			
			
			
                 if (0 == selector) DS_time_temp[selector] %= 60;   //seconds
            else if (1 == selector) DS_time_temp[selector] %= 60;   //minutes
            else if (2 == selector) DS_time_temp[selector] %= 24;   //hours
            else if (3 == selector)//days
			{
				DS_time_temp[selector] %=8;
				
				if(0 == DS_time_temp[selector]) DS_time_temp[selector] = 1;
			}     
            else if (4 == selector) DS_time_temp[selector] %= 31;   //date
            else if (5 == selector) DS_time_temp[selector] %= 12;   //months
            else if (6 == selector) DS_time_temp[selector] %= 50;   //years
            //////////////////////////////////////////////////////////////////////////
        }
        else if (1 == manual_mode)
        {
            if (1 == manual_mode)  TOG_BIT(running_timers, selector);  // running_timers = ( running_timers & (~(1<<selector)) ) | ( (  !( (running_timers >> selector )&1 ) ) << selector )  ;

        }




        while (0 == READ_BIT(PINC, UP_BT));
    }
    //////////////////////////////////////////////////////////////////////////

}



ISR(PCINT0_vect)
{
    for (uint16 i = 1; i!=0 ;i++); //delay
	
	
	//////////////////////////////////////////////////////////////////////////
	////     OK button

    if (0 == READ_BIT(PINB, OK_BT)) 
    {

        
         //////////////////////////////////////////////////////////////////////////
		 //
        if (1 == set_timers_mode)
        {
            
			
			
			//save the new or edit timer
			if(display_timer_properties == 0)
			{
				if ( 0 == timers.timer_properties.on_off ) UTILITy_save_timer();
				else                                       UTILITy_remove_timer();
				
			}
			
			
				display_timer_properties = display_timer_properties == 0 ? 1 : 0;
                selector = 1;
			
			
			
        }
		//////////////////////////////////////////////////////////////////////////
		
        OK = 1;

        while (0 == READ_BIT(PINB, OK_BT));

    }


    //////////////////////////////////////////////////////////////////////////
	//// right button
    if (0 == READ_BIT(PINB, RIGHT_BT)) 
    {
   
        selector++;
        selector = set_timers_mode == 1 ? selector % 21 : selector % 8;
           

        while (0 == READ_BIT(PINB, RIGHT_BT));
    }
	//////////////////////////////////////////////////////////////////////////
	
	
}
//////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
//        timer1 overfolw 


ISR(TIMER1_OVF_vect)
{
	////////////////////////////////////////////////////////////////////////////
	// res avr if hang on 
	
	if(prev_second == DS_time[0]) CLR_BIT(PORTD,1);
	else   prev_second = DS_time[0];
	
	//////////////////////////////////////////////////////////////////////////
	
	
	
	
	//////////////////////////////////////////////////////////////////////////
	if (0 == manual_mode)
	{
		timerUp temp_timers = timers;
		uint8   temp_timer_chnager = timer_changer;
		//////////////////////////////////////////////////////////////////////////
		//   disable global interrupt
		//CLR_BIT(SREG,7);
		//////////////////////////////////////////////////////////////////////////
		
		
		
		//////////////////////////////////////////////////////////////////////////
		//   _get_running_timers
		timer_changer = 1;
		running_timers = 0;
		
		TOG_BIT(PORTD,0);
		
		UTILITY_get_running_timers();
		
		
		//////////////////////////////////////////////////////////////////////////
		//   enable global interrupt
		//SET_BIT(SREG,7);
		//////////////////////////////////////////////////////////////////////////
		
		timer_changer = temp_timer_chnager;
		timers = temp_timers;
		
		
		//////////////////////////////////////////////////////////////////////////
		// calibrate time
		DS1307_read_time(DS_time);
		if (DS_time[4] != date_counter)
		{
			
			DS_time_temp[0] = DS_time[0];
			DS_time_temp[1] = DS_time[1];
			DS_time_temp[2] = DS_time[2];
			DS_time_temp[3] = DS_time[3];
			DS_time_temp[4] = DS_time[4];
			DS_time_temp[5] = DS_time[5];
			DS_time_temp[6] = DS_time[6];
			date_counter = DS_time[4];
			
			
			if(DS_time_temp[0]+8 > 59)
			{
				if(DS_time_temp[1]+1 > 59)
				{
					if(DS_time_temp[2]+1 > 23)
					{
						DS_time_temp[4] = 0;
						DS_time_temp[3] = DS_time_temp[3] == 7 ? 1 :DS_time_temp[3]+1;
						DS_time_temp[2] = 0;
						DS_time_temp[1] = 0;
						DS_time_temp[0] = (8-(59-DS_time_temp[0]));
						
					}
					else
					{
						DS_time_temp[2]++;
						DS_time_temp[1]++;
						DS_time_temp[0] += (8-(59-DS_time_temp[0]));
					}
				}
				else
				{
					DS_time_temp[1]++;
					DS_time_temp[0] += (8-(59-DS_time_temp[0]));
				}
			}
			else DS_time_temp[0]+=8;
			 
			DS1307_save_time(DS_time_temp);
		}
		
	}
	
	

}
