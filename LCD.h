/*
 * LCD.h
 *
 * Created: 8/16/2022 11:46:35 PM
 *  Author: effic
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "STD_MACROS.h"

#define INIT_PINS_OUT (DDRD |= 0B11100000,DDRB |= 0B00000111)
					  


#define RS(x)(  x==1 ? SET_BIT(PORTB,2) : CLR_BIT(PORTB,2))
#define EN(x)(  x==1 ? SET_BIT(PORTB,1) : CLR_BIT(PORTB,1))

#define D4(x)(  x==1 ? SET_BIT(PORTB,0) : CLR_BIT(PORTB,0))
#define D5(x)(  x==1 ? SET_BIT(PORTD,7) : CLR_BIT(PORTD,7))
#define D6(x)(  x==1 ? SET_BIT(PORTD,6) : CLR_BIT(PORTD,6))
#define D7(x)(  x==1 ? SET_BIT(PORTD,5) : CLR_BIT(PORTD,5))


void LCD_init_4(void);
void LCD_write_command(uint8_t command);
void LCD_check_busy(void);
void LCD_write_chararcter(uint8_t ch);
void LCD_write_string(char str[]);
void LCD_write_num(uint64_t num);
void LCD_y_x(uint8_t y, uint8_t x);
void LCD_clear(void);
void LCD_create_shape(uint8_t arr[],uint8 location);

void LCD_write_float(float num ,uint8 precision);

#endif /* LCD_H_ */