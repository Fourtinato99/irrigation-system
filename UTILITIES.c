/*
 * UTILITIES.c
 *
 * Created: 8/22/2022 10:06:41 PM
 *  Author: effic
 */
#include "UTILITIES.h"




void UTILITY_delay_ms(uint16 second)
{
    uint16 j;
    for (uint16 i = 0; i < second; i++) {
        for (j = 0; j < 4000;j++);

    }


}

void UTILITY_display_time(volatile uint8 DS_time[])
{

    //////////////////////////////////////////////////////////////////////////
    //      first create custom shape 

    if (1 == time_mode_flag)
    {
        time_mode_flag = 0;
        uint8 setting0[] = {
            0B00101,
            0B00101,
            0B00101,
            0B11111,
            0B00100,
            0B11100,
            0B00100,
            0B11100
        };

        uint8 setting1[] = {
            0B10100,
            0B10100,
            0B10100,
            0B11111,
            0B00100,
            0B00111,
            0B00100,
            0B00111
        };

        uint8 setting2[] = {
            0B11100,
            0B00100,
            0B11100,
            0B00100,
            0B11111,
            0B00101,
            0B00101,
            0B00101
        };
        uint8 setting3[] = {
            0B00111,
            0B00100,
            0B00111,
            0B00100,
            0B11111,
            0B10100,
            0B10100,
            0B10100
        };

        uint8 arrow_left[] = {
            0B00001,
            0B00011,
            0B00111,
            0B11111,
            0B11111,
            0B00111,
            0B00011,
            0B00001
        };

        uint8 arrow_right[] = {
            0B10000,
            0B11000,
            0B11100,
            0B11111,
            0B11111,
            0B11100,
            0B11000,
            0B10000
        };

        LCD_create_shape(setting0, 0);
        LCD_create_shape(setting1, 1);
        LCD_create_shape(setting2, 2);
        LCD_create_shape(setting3, 3);
        LCD_create_shape(arrow_left, 4);
        LCD_create_shape(arrow_right, 5);
    }
    //////////////////////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////////////////////
    //then display the time in selector mode

    if (1 == set_time_mode)
    {
        LCD_y_x(1, 1);
        LCD_write_chararcter(0);
        LCD_write_chararcter(1);
        LCD_write_string(" ");



        if (2 == selector) //hours
        {
            LCD_write_chararcter(4);
            LCD_write_num(DS_time[2]);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_num(DS_time[2]);
        }


        LCD_write_string(":");


        if (1 == selector) //minutes
        {
            LCD_write_chararcter(4);
            LCD_write_num(DS_time[1]);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_num(DS_time[1]);
        }



        LCD_write_string(":");

        if (0 == selector)   //seconds
        {
            LCD_write_chararcter(4);
            LCD_write_num(DS_time[0]);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_num(DS_time[0]);
        }




        LCD_write_string(" /");


        if (3 == selector)   //days
        {
            LCD_write_chararcter(4);
            LCD_write_num(DS_time[3] + 1);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_num(DS_time[3] + 1);
        }


        LCD_write_string("        ");





        LCD_y_x(2, 1);
        LCD_write_chararcter(2);
        LCD_write_chararcter(3);
        LCD_write_string(" ");

        if (6 == selector) //years
        {
            LCD_write_chararcter(4);
            LCD_write_string("20");
            LCD_write_num(DS_time[6]);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_string("20");
            LCD_write_num(DS_time[6]);
        }




        LCD_write_string("/");



        if (5 == selector) //months
        {
            LCD_write_chararcter(4);
            LCD_write_num(DS_time[5] + 1);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_num(DS_time[5] + 1);
        }



        LCD_write_string("/");



        if (4 == selector)  //data of month
        {
            LCD_write_chararcter(4);
            LCD_write_num(DS_time[4] + 1);
            LCD_write_chararcter(5);
        }
        else {
            LCD_write_num(DS_time[4] + 1);
        }

        LCD_write_string("      ");





    }
    else
    {
        LCD_y_x(1, 1);
        LCD_write_string("   ");




        LCD_write_num(DS_time[2]);
        LCD_write_string(":");
        LCD_write_num(DS_time[1]);
        LCD_write_string(":");
        LCD_write_num(DS_time[0]);
        LCD_write_string(" / ");
        LCD_write_num(DS_time[3] + 1);  //days
        LCD_write_string("        ");

        LCD_y_x(2, 1);
        LCD_write_string("   ");

        LCD_write_string("20");
        LCD_write_num(DS_time[6]); //years
        LCD_write_string("/");
        LCD_write_num(DS_time[5] + 1); //months
        LCD_write_string("/");
        LCD_write_num(DS_time[4] + 1); //date of month
        LCD_write_string("     ");

    }

}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//display manual screen



void UTILITY_display_manual(volatile uint8 running_timers_temp)
{

    //////////////////////////////////////////////////////////////////////////
    //   first create custom shape
    if (1 == manual_flag)
    {
        manual_flag = 0;
        uint8 hand_0[] = {
            0B00000,
            0B00000,
            0B00001,
            0B00101,
            0B00101,
            0B10101,
            0B10101,
            0B10101
        };


        uint8 hand_1[] = {
            0B00000,
            0B00000,
            0B01000,
            0B01000,
            0B01010,
            0B01010,
            0B01010,
            0B01010
        };
        uint8 hand_2[] = {
            0B10101,
            0B11111,
            0B11111,
            0B01111,
            0B00111,
            0B00111,
            0B00111,
            0B00111
        };
        uint8 hand_3[] = {
            0B01010,
            0B11110,
            0B11110,
            0B11110,
            0B11100,
            0B11100,
            0B11100,
            0B11100
        };
        uint8 arrow_left[] = {
            0B00001,
            0B00011,
            0B00111,
            0B11111,
            0B11111,
            0B00111,
            0B00011,
            0B00001
        };

        uint8 arrow_right[] = {
            0B10000,
            0B11000,
            0B11100,
            0B11111,
            0B11111,
            0B11100,
            0B11000,
            0B10000
        };

        uint8 on[] = {

            0B11111,
            0B10001,
            0B10001,
            0B10001,
            0B10001,
            0B10001,
            0B10001,
            0B11111,

        };

        uint8 off[] = {
             0B10001,
             0B10001,
             0B11010,
             0B01110,
             0B00100,
             0B01010,
             0B11011,
             0B10001
        };

        LCD_create_shape(hand_0, 0);
        LCD_create_shape(hand_1, 1);

        LCD_create_shape(hand_2, 2);
        LCD_create_shape(hand_3, 3);

        LCD_create_shape(arrow_left, 4);
        LCD_create_shape(arrow_right, 5);

        LCD_create_shape(on, 6);
        LCD_create_shape(off, 7);
    }


    LCD_y_x(1, 1);
    for (uint8 i = 0;i < 8; i++)
    {
        if (i == selector)
        {
            LCD_write_string(" ");
            LCD_write_chararcter(4);
            LCD_write_num(i + 1);
            LCD_write_chararcter(5);
            LCD_write_string(" ");
        }
        else     LCD_write_num(i + 1);

    }

    LCD_write_string("          ");

    LCD_y_x(2, 1);

    for (uint8 i = 0;i < 8; i++)
    {
        if (i == selector)
        {
            LCD_write_string(" ");
            LCD_write_chararcter(4);

            if (1 == ((running_timers_temp >> i) & 1))   LCD_write_chararcter(6);
            else                                       LCD_write_chararcter(7);

            LCD_write_chararcter(5);
            LCD_write_string(" ");
        }
        else
        {
            if (1 == ((running_timers_temp >> i) & 1))   LCD_write_chararcter(6);
            else                                       LCD_write_chararcter(7);
        }

    }
    LCD_write_string("          ");

}
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
void UTILITY_display_timer(void)
{


    //////////////////////////////////////////////////////////////////////////
    // create custom shape
    if (1 == timer_flag)
    {
        uint8 arrow_left[] = {
            0B00001,
            0B00011,
            0B00111,
            0B11111,
            0B11111,
            0B00111,
            0B00011,
            0B00001
        };

        uint8 arrow_right[] = {
            0B10000,
            0B11000,
            0B11100,
            0B11111,
            0B11111,
            0B11100,
            0B11000,
            0B10000
        };

        uint8 on[] = {

            0B11111,
            0B10001,
            0B10001,
            0B10001,
            0B10001,
            0B10001,
            0B10001,
            0B11111,

        };

        uint8 off[] = {
            0B10001,
            0B10001,
            0B11010,
            0B01110,
            0B00100,
            0B01010,
            0B11011,
            0B10001
        };

        uint8 timer[] = {
            0B11111,
            0B11111,
            0B11111,
            0B11111,
            0B11111,
            0B11111,
            0B01110,
            0B01110
        };
		
		uint8 start[] = {
			0B00001,
			0B10001,
			0B11001,
			0B11101,
			0B11101,
			0B11001,
			0B10001,
			0B00001
		};
		
		uint8 period[] = {
			0B10001,
			0B10001,
			0B10001,
			0B11111,
			0B11111,
			0B10001,
			0B10001,
			0B10001
		};

        LCD_create_shape(off, 0);
        LCD_create_shape(on, 1);
       
        LCD_create_shape(arrow_left, 2);
        LCD_create_shape(arrow_right, 3);
        LCD_create_shape(timer, 4);
		LCD_create_shape(start, 5);
		LCD_create_shape(period, 6);


        timer_flag = 0;


    }



    //timerUp timer = { .timer_properties.start_hours = 8 };
    //////////////////////////////////////////////////////////////////////////
    // display number of timers
    LCD_y_x(1, 1);
    LCD_write_num(timer_changer);
    LCD_write_string("   ");



    //////////////////////////////////////////////////////////////////////////
    //  display whether ON or OFF

    LCD_y_x(1, 4);
    LCD_write_chararcter(timers.timer_properties.on_off);
    LCD_write_string(" ");

    //////////////////////////////////////////////////////////////////////////
    // display start time
 
    LCD_write_num(timers.timer_properties.start_hours);
    LCD_write_string(":");
    LCD_write_num(timers.timer_properties.start_minutes);
    LCD_write_string(" ");

    //////////////////////////////////////////////////////////////////////////
    //   display period 
	

    LCD_write_num(timers.timer_properties.period_hours);
    LCD_write_string(":");
    LCD_write_num(timers.timer_properties.period_minutes);
    LCD_write_string("                 ");


    LCD_y_x(2, 1);
    //////////////////////////////////////////////////////////////////////////
    //   display running timers

    timers.timer_properties.timer1 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('1');
    timers.timer_properties.timer2 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('2');
    timers.timer_properties.timer3 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('3');
    timers.timer_properties.timer4 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('4');
    timers.timer_properties.timer5 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('5');
    timers.timer_properties.timer6 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('6');
    timers.timer_properties.timer7 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('7');
    timers.timer_properties.timer8 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('8');
    LCD_write_string(" ");

    //////////////////////////////////////////////////////////////////////////
    //   display days that 

    timers.timer_properties.day1 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('1');
    timers.timer_properties.day2 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('2');
    timers.timer_properties.day3 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('3');
    timers.timer_properties.day4 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('4');
    timers.timer_properties.day5 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('5');
    timers.timer_properties.day6 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('6');
    timers.timer_properties.day7 == 0 ? LCD_write_chararcter(0) : LCD_write_chararcter('7');

}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////7
//////////////////////////////////////////////////////////////////////////
// 
/*
function name :UTILITY_get_bits
description   :get number of contiguous bits

return   : bits

*/

uint32 UTILITY_get_bits(volatile uint32* var, uint8 num, uint8 bit)
{
    uint32 mask = 0;
    while (num)
    {
        mask = (mask << 1) | 1;
        num--;
    }
    return (*var >> bit) & mask;
}
//////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/* function name : UTILITY_display_selector_timer.
   description   :display selector timer properties.

   return        : void

*/
void UTILITY_display_edit_timer(void)
{
    if (8 >= selector)  //display status of of timer and days
    {
        LCD_y_x(1, 1);
        LCD_write_string("status:  ");

        selector == 1 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.on_off), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.on_off);
        LCD_write_string("        ");

        LCD_y_x(2, 1);
        LCD_write_string("Days: ");

        selector == 2 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day1), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day1);
        selector == 3 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day2), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day2);
        selector == 4 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day3), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day3);
        selector == 5 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day4), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day4);
        selector == 6 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day5), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day5);
        selector == 7 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day6), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day6);
        selector == 8 ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.day7), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.day7);
        LCD_write_string("       ");

        /*

        //////////////////////////////////////////////////////////////////////////
        //display whether timer on or off
        LCD_y_x(1,1);
        LCD_write_string("status:  ");


        if(1 == selector)
        {

            //LCD_write_chararcter(2);
            //LCD_write_chararcter(timers.timer_properties.on_off);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.on_off);
        LCD_write_string("                 ");
        //////////////////////////////////////////////////////////////////////////


        LCD_y_x(2,1);
        LCD_write_string("days: ");


        //////////////////////////////////////////////////////////////////////////
        //display status day1

        if(2 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day1);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day1);

        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        //display status day2
        if(3 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day2);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day2);
        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        //display status day3
        if(4 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day3);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day3);
        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        //display status day4
        if(5 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day4);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day4);
        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        //display status day5
        if(6 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day5);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day5);
        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        //display status day6
        if(7 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day6);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day6);
        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        //display status day7
        if(8 == selector)
        {
            LCD_write_chararcter(2);
            LCD_write_chararcter(timers.timer_properties.day7);
            LCD_write_chararcter(3);
        }
        else    LCD_write_chararcter(timers.timer_properties.day7);
        //////////////////////////////////////////////////////////////////////////


        LCD_write_string("   ");
       */
    }

    //////////////////////////////////////////////////////////////////////////
    //   start timer and period
    else if (16 >= selector && 8 < selector)
    {
        LCD_y_x(1, 1);
        LCD_write_chararcter(4);
        LCD_write_chararcter(4);
        LCD_write_string("  ");

         9 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('1'), LCD_write_chararcter(3)) : LCD_write_chararcter('1');
        10 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('2'), LCD_write_chararcter(3)) : LCD_write_chararcter('2');
        11 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('3'), LCD_write_chararcter(3)) : LCD_write_chararcter('3');
        12 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('4'), LCD_write_chararcter(3)) : LCD_write_chararcter('4');
        13 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('5'), LCD_write_chararcter(3)) : LCD_write_chararcter('5');
        14 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('6'), LCD_write_chararcter(3)) : LCD_write_chararcter('6');
        15 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('7'), LCD_write_chararcter(3)) : LCD_write_chararcter('7');
        16 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter('8'), LCD_write_chararcter(3)) : LCD_write_chararcter('8');
        LCD_write_string("      ");



        LCD_y_x(2, 1);
        LCD_write_chararcter(4);
        LCD_write_chararcter(4);
        LCD_write_string("  ");

         9 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer1), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer1);
        10 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer2), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer2);
        11 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer3), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer3);
        12 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer4), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer4);
        13 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer5), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer5);
        14 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer6), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer6);
        15 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer7), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer7);
        16 == selector ? (LCD_write_chararcter(2), LCD_write_chararcter(timers.timer_properties.timer8), LCD_write_chararcter(3)) : LCD_write_chararcter(timers.timer_properties.timer8);

        LCD_write_string("     ");

    }
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    // display start time and period

    if (17 <= selector && 20 >= selector)
    {
        //////////////////////////////////////////////////////////////////////////
        //    start time
        LCD_y_x(1, 1);
        LCD_write_string("start:  ");

        17 == selector ? (LCD_write_chararcter(2), LCD_write_num(timers.timer_properties.start_hours), LCD_write_chararcter(3)) : LCD_write_num(timers.timer_properties.start_hours);
        LCD_write_string(":");
        18 == selector ? (LCD_write_chararcter(2), LCD_write_num(timers.timer_properties.start_minutes), LCD_write_chararcter(3)) : LCD_write_num(timers.timer_properties.start_minutes);
        LCD_write_string("            ");
        //////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////
        //  period time

        LCD_y_x(2, 1);
        LCD_write_string("period:  ");

        19 == selector ? (LCD_write_chararcter(2), LCD_write_num(timers.timer_properties.period_hours), LCD_write_chararcter(3)) : LCD_write_num(timers.timer_properties.period_hours);
        LCD_write_string(":");
        20 == selector ? (LCD_write_chararcter(2), LCD_write_num(timers.timer_properties.period_minutes), LCD_write_chararcter(3)) : LCD_write_num(timers.timer_properties.period_minutes);
        LCD_write_string("            ");
    }




}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// get timer properties from EEPROM
void UTILITY_get_timer_EEPROM(void)
{
	
	timers.timer =  timer_changer == 0 ? 0 : EEPROM_read_64( (timer_changer+1)*8);
}
//////////////////////////////////////////////////////////////////////////
 





//////////////////////////////////////////////////////////////////////////
//save timer to eeprom
void UTILITY_save_timer_EEPROM(void)
{
	EEPROM_write_64( (timer_changer+1)*8,timers.timer);
	
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
/// get the index of the next position if it empty or full

void UTILITY_get_next_timer_index(uint8 num )
{
	while(1)
	{
		if(0 == timer_changer )                                   timer_changer = 1;
		else if(  timer_changer >= 64   )                         break;
		else if( ((all_timers.lower >> timer_changer)&1) == num ) return ;
		else                                                      timer_changer++;
		
		//((all_timers.lower >> timer_changer)&1) == num ? return :timer_changer++;
		
	}
	while(1)
	{
		if(timer_changer == 128)
		{
			timer_changer = 0;
			return ;
		}
		else if( ((all_timers.upper >> (timer_changer%64) )&1) == num ) return ;
		else                                                      timer_changer++;
		//((all_timers.upper >> timer_changer)&1) == num ? return :timer_changer++;
		
	}

}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//          

void UTILITY_re_set_timer_bit(void)
{
	if (0 == timer_changer )            CLR_BIT( all_timers.lower ,0);
	else if(timer_changer < 64)         TOG_BIT( all_timers.lower , timer_changer    );
	else                                TOG_BIT( all_timers.upper , timer_changer%64 );
	
	
	EEPROM_write_64(0,all_timers.lower);
	EEPROM_write_64(8,all_timers.upper);
	
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// set new timer or edit existint timer
void UTILITy_save_timer(void)
{
	UTILITY_re_set_timer_bit();
	UTILITY_get_next_timer_index(0);
	UTILITY_re_set_timer_bit();
	UTILITY_save_timer_EEPROM();
	
}
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// remove new timer or edit existing timer
void UTILITy_remove_timer(void)
{
	UTILITY_re_set_timer_bit();
	
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//    function get all running time in the same time
void UTILITY_get_running_timers(void)
{
	
	while(0 != timer_changer )
	{
		UTILITY_get_timer_EEPROM();
		UTILITY_running_or_not();
		timer_changer++;
		UTILITY_get_next_timer_index(1);
	}
}
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// 
void UTILITY_running_or_not(void)
{
	uint8 day_on = 0;
	uint8 time_on = 0;
	if(1 == timers.timer_properties.on_off)
	{
		//////////////////////////////////////////////////////////////////////////
		     if(timers.timer_properties.day1 == 1 && DS_time[3] == 1) day_on= 1;
		else if(timers.timer_properties.day2 == 1 && DS_time[3] == 2) day_on= 1;
		else if(timers.timer_properties.day3 == 1 && DS_time[3] == 3) day_on= 1;
		else if(timers.timer_properties.day4 == 1 && DS_time[3] == 4) day_on= 1;
		else if(timers.timer_properties.day5 == 1 && DS_time[3] == 5) day_on= 1;
		else if(timers.timer_properties.day6 == 1 && DS_time[3] == 6) day_on= 1;
		else if(timers.timer_properties.day7 == 1 && DS_time[3] == 7) day_on= 1;
		//////////////////////////////////////////////////////////////////////////
		
		
		//////////////////////////////////////////////////////////////////////////
		//  determine whether the time in range or not
		if (1 == day_on)
		{
			if(DS_time[2] >=   timers.timer_properties.start_hours )  // start hours
			{
				if( DS_time[2]==timers.timer_properties.start_hours )
				{
					if(DS_time[1] >= timers.timer_properties.start_minutes )  //start minutes
					{
						if (timers.timer_properties.period_hours >= DS_time[2])  //end hours
						{
							if(timers.timer_properties.period_hours == DS_time[2])
							{
								if (timers.timer_properties.period_minutes > DS_time[1]) time_on = 1;// end minutes
							}
							else time_on = 1;
						}
					}
				}else
				{
					if (timers.timer_properties.period_hours >= DS_time[2]) //end hours
					{
						if(timers.timer_properties.period_hours == DS_time[2])
						{
							if (timers.timer_properties.period_minutes >  DS_time[1]) time_on = 1; ///end minutes
						}
						else   time_on = 1;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			
			
			//////////////////////////////////////////////////////////////////////////
			if( 1 == time_on )
			{
				timers.timer_properties.timer1 == 1 ? SET_BIT(running_timers,0):CLR_BIT(running_timers,0);
				timers.timer_properties.timer2 == 1 ? SET_BIT(running_timers,1):CLR_BIT(running_timers,1);
				timers.timer_properties.timer3 == 1 ? SET_BIT(running_timers,2):CLR_BIT(running_timers,2);
				timers.timer_properties.timer4 == 1 ? SET_BIT(running_timers,3):CLR_BIT(running_timers,3);
				timers.timer_properties.timer5 == 1 ? SET_BIT(running_timers,4):CLR_BIT(running_timers,4);
				timers.timer_properties.timer6 == 1 ? SET_BIT(running_timers,5):CLR_BIT(running_timers,5);
				timers.timer_properties.timer7 == 1 ? SET_BIT(running_timers,6):CLR_BIT(running_timers,6);
				timers.timer_properties.timer8 == 1 ? SET_BIT(running_timers,7):CLR_BIT(running_timers,7);

			}
			//////////////////////////////////////////////////////////////////////////
			
			
			
			
		}
		
		
	}
}
