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

volatile uint8 manual_mode = 0;
volatile uint8 DS_time[7] = { 0 };

// set timers variables
volatile uint8 set_timers_mode;
volatile uint32 timer_properties;

volatile timerUp timers ;
volatile all all_timers ;


volatile uint8 timer_changer;

volatile uint8 timer_flag;
volatile uint8 display_timer_properties;
volatile uint8 selector;

volatile uint8 selector = 0;

volatile uint8 DS_time_temp[7] = { 0 };
volatile uint8 OK = 0;

volatile uint8 running_timers = 0;

volatile uint8 time_mode_flag = 0;
volatile uint8 manual_flag = 0;


int main(void)
{
	
	
	//////////////////////////////////////////////////////////////////////////
    /* Replace with your application code */
    //initiating LCD
    LCD_init_4();

	//////////////////////////////////////////////////////////////////////////
	
	
	

     //////////////////////////////////////////////////////////////////////////
    //initiating shift register 
    SHIFT_REGISTER_init();
	SHIFT_REGISTER_OUT(0);
	//////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////
	// intiating timer overflow
	TIMER1_init_normal(5);

		

	

    //////////////////////////////////////////////////////////////////////////
    //initiating I2C master
    I2C_master_init(50);
    I2C_master_start();
	//////////////////////////////////////////////////////////////////////////
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// get all_timer
	if(1 == (EEPROM_read_64(0) & 1) )
	{
		EEPROM_write_64(0,0);
		EEPROM_write_64(8,0);
		
	}
	
	all_timers.lower = EEPROM_read_64(0);
	all_timers.upper = EEPROM_read_64(8);
	//////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////
    //initiating interrupt for buttons using pin change interrupt
     //1-set pins as input with pull up
    CLR_BIT(DDRD, 0);   //set time  and data button
    SET_BIT(PORTD, 0);	//pull up

    CLR_BIT(DDRD, 1);   //set timers button
    SET_BIT(PORTD, 1);	//pull up

    CLR_BIT(DDRD, 2);   //run manual button
    SET_BIT(PORTD, 2);	//pull up

    CLR_BIT(DDRD, 3);   //up button
    SET_BIT(PORTD, 3);   //pull up

    SET_BIT(DDRD, 4);   //down button
    SET_BIT(PORTD, 4);

    CLR_BIT(DDRC, 0);    //cancel button
    SET_BIT(PORTC, 0);    //pull up

    CLR_BIT(DDRC, 1);    //ok button
    SET_BIT(PORTC, 1);    //pull up

    CLR_BIT(DDRC, 2);    //right button
    SET_BIT(PORTC, 2);    //pull up


	
	//////////////////////////////////////////////////////////////////////////
	
	
	
	
    //////////////////////////////////////////////////////////////////////////
    //set interrupt pins
    INTERRUPT_PC_init(9);   //pin change interrupt of PINC 1 ==>ok button

    INTERRUPT_PC_init(10);   //pin change interrupt of PINC 1 ==>right button

    INTERRUPT_PC_init(16);   //pin change interrupt of PIND 0 ==>set time button

    INTERRUPT_PC_init(17);   //pin change interrupt of PIND 1 ==>set timers button

    INTERRUPT_PC_init(18);   //pin change interrupt of PIND 2 ==>manual button

    INTERRUPT_PC_init(19);   //pin change interrupt of PIND 3 ==>up button
	//////////////////////////////////////////////////////////////////////////




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







ISR(PCINT2_vect)
{
    for (uint16 i = 0;i < 60000;i++); //delay

    if (0 == READ_BIT(PIND, 0)) //set time button isr
    {
        set_time_mode = set_time_mode == 0 ? 1 : 0;
        manual_mode = 0;
        manual_flag = 0;
        set_timers_mode = 0;
        time_mode_flag = 1;

        DS_time_temp[0] = DS_time[0];
        DS_time_temp[1] = DS_time[1];
        DS_time_temp[2] = DS_time[2];
        DS_time_temp[3] = DS_time[3];
        DS_time_temp[4] = DS_time[4];
        DS_time_temp[5] = DS_time[5];
        DS_time_temp[6] = DS_time[6];

        while (0 == READ_BIT(PIND, 0));
    }
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    //        set timers button ISR

    if (0 == READ_BIT(PIND, 1))
    {
        set_time_mode = 0;
        manual_mode = 0;
        selector = 0;
        manual_flag = 0;
        time_mode_flag = 0;
		timers.timer = 0;
		timer_changer = 0;


        timer_flag = 1;
        selector = 1;
        display_timer_properties = 1 ;
        set_timers_mode = set_timers_mode == 0 ? 1 : 0;
		


        while (0 == READ_BIT(PIND, 1));  //waiting until removing his fucking finger

    }
    //////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////
    //        manual button ISR

    if (0 == READ_BIT(PIND, 2))
    {
        set_time_mode = 0;
        set_timers_mode = 0;
        selector = 0;
        manual_mode = manual_mode == 0 ? 1 : 0;
        manual_flag = 1;

        while (0 == READ_BIT(PIND, 2));  //waiting until removing his fucking finger

    }
    //////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////
    //up button  isr
    if (0 == READ_BIT(PIND, 3))
    {

        if (1 == set_timers_mode )
        {
			//////////////////////////////////////////////////////////////////////////
			//    controller of timer changer
			if(display_timer_properties == 1)
			{
				timer_changer++;
				UTILITY_get_next_timer_index(1);
				UTILITY_get_timer_EEPROM();	
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
            else if (17 == selector) timers.timer_properties.start_hours++;
            else if (18 == selector) timers.timer_properties.start_minutes++;
            else if (19 == selector) timers.timer_properties.period_hours++;
            else if (20 == selector) timers.timer_properties.period_minutes++;
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
            else if (3 == selector) DS_time_temp[selector] %= 7;    //days
            else if (4 == selector) DS_time_temp[selector] %= 31;   //date
            else if (5 == selector) DS_time_temp[selector] %= 12;   //months
            else if (6 == selector) DS_time_temp[selector] %= 50;   //years
            //////////////////////////////////////////////////////////////////////////
        }
        else if (1 == manual_mode)
        {
            if (1 == manual_mode)  TOG_BIT(running_timers, selector);  // running_timers = ( running_timers & (~(1<<selector)) ) | ( (  !( (running_timers >> selector )&1 ) ) << selector )  ;

        }




        while (0 == READ_BIT(PIND, 3));
    }
    //////////////////////////////////////////////////////////////////////////

}



ISR(PCINT1_vect)
{
    for (uint16 i = 0;i < 60000;i++); //delay
	
	
	//////////////////////////////////////////////////////////////////////////
	////     OK button

    if (0 == READ_BIT(PINC, 1)) 
    {

        
         //////////////////////////////////////////////////////////////////////////
		 //
        if (1 == set_timers_mode)
        {
            
			
			
			//save the new or edit timer
			if(display_timer_properties == 0)
			{
				if ( 1 == timers.timer_properties.on_off ) UTILITy_save_timer();
				else                                       UTILITy_remove_timer();
				
			}
			display_timer_properties = display_timer_properties == 0 ? 1 : 0;
            selector = 1;
        }
		//////////////////////////////////////////////////////////////////////////
		
        OK = 1;

        while (0 == READ_BIT(PINC, 1));

    }


    //////////////////////////////////////////////////////////////////////////
	//// right button
    if (0 == READ_BIT(PINC, 2)) 
    {
   
        selector++;
        selector = set_timers_mode == 1 ? selector % 21 : selector % 8;
           

        while (0 == READ_BIT(PINC, 2));
    }
	//////////////////////////////////////////////////////////////////////////
	
	
}
//////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
//        timer1 overfolw 


ISR(TIMER1_OVF_vect)
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
	
	TOG_BIT(PORTD,4);
	
	UTILITY_get_running_timers();
	
	
	//////////////////////////////////////////////////////////////////////////
	//   enable global interrupt
	//SET_BIT(SREG,7);
	//////////////////////////////////////////////////////////////////////////
	
	timer_changer = temp_timer_chnager;
	timers = temp_timers;
	

}