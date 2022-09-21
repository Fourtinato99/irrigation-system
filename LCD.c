/*
 * LCD.c
 *
 * Created: 8/16/2022 11:47:01 PM
 *  Author: effic
 */ 
#include "LCD.h"


void LCD_init_4(void){
	
	INIT_PINS_OUT(0xFF); //initiate pins as output
	_delay_ms(10);  //wait for stable power
	
	EN(0);
	
	
	LCD_write_command(0x33);
	LCD_write_command(0x32);
	LCD_write_command(0x28);
	
	
	LCD_write_command(0x6);
	LCD_write_command(0xc);
	LCD_write_command(0x1);
	//LCD_write_command(0xf);
	
	_delay_ms(6);
}



void LCD_write_command(uint8_t command){
	
	
	
	RS(0);
	
	D4( ((command>>4) & 1) );
	D5( ((command>>5) & 1) );
	D6( ((command>>6) & 1) );
	D7( ((command>>7) & 1) );
	
	EN(1);
	_delay_ms(1);
	EN(0);
	
	//_delay_ms(1);
	
	D4( ((command>>0) & 1) );
	D5( ((command>>1) & 1) );
	D6( ((command>>2) & 1) );
	D7( ((command>>3) & 1) );
	
	EN(1);
	_delay_ms(1);
	EN(0);
	
	
	
	
	
	
}




void LCD_y_x(uint8_t y, uint8_t x){
	
	uint8_t adresses[]={0x80 , 0xc0}; 
	
	LCD_write_command(adresses[y-1]+x-1);
	//_delay_ms(4);
}

void LCD_write_chararcter(uint8_t ch){
	
	_delay_ms(1);
	RS(1);
	
	D4( ((ch>>4) & 1) );
	D5( ((ch>>5) & 1) );
	D6( ((ch>>6) & 1) );
	D7( ((ch>>7) & 1) );
	
	EN(1);
	_delay_ms(1);
	EN(0);
	
	//_delay_ms(1);
	
	
	D4( ((ch>>0) & 1) );
	D5( ((ch>>1) & 1) );
	D6( ((ch>>2) & 1) );
	D7( ((ch>>3) & 1) );
	
	EN(1);
	_delay_ms(1);
	EN(0);
	
}

void LCD_write_string(char str[]){
	
	int  counter = 0;
	while( counter<32 && str[counter] !='\0')
	{
		 LCD_write_chararcter(str[counter]);
		 counter++;
	}
}


void LCD_write_num(uint64_t num){
	
	if(num == 0){
		LCD_write_chararcter('0');
		return ;
		
	}else{
		uint64_t temp = 0;
		uint8 counter = 0;
		while(num != 0)
		{
			temp =temp*10+ num%10 ;
			num = num/10;
			counter++;
		}
		
		while( (temp != 0) | (counter > 0) ){
			LCD_write_chararcter( temp%10 +48);
			temp = temp /10;
			counter--;
			
		}
	}
}

void LCD_clear(void){
	_delay_ms(6);
	LCD_write_command(0x01);
}



void LCD_write_float(float num ,uint8 precision){
	
	if(precision > 6) precision = 6;
	
	LCD_write_num(num);
	LCD_write_chararcter('.');
	num = num - (uint64)num ;
	while(precision) {
		num *=10;
		precision--;
	}
	num=num;
	LCD_write_num(num);
	
}

void LCD_create_shape(uint8_t arr[],uint8 location)
{
	LCD_write_command(0b01000000 | (location << 3) );
	
	LCD_write_chararcter(arr[0]);
	LCD_write_chararcter(arr[1]);
	LCD_write_chararcter(arr[2]);
	LCD_write_chararcter(arr[3]);
	
	LCD_write_chararcter(arr[4]);
	LCD_write_chararcter(arr[5]);
	LCD_write_chararcter(arr[6]);
	LCD_write_chararcter(arr[7]);
}