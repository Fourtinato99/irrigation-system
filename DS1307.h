/*
 * DS1307.h
 *
 * Created: 9/14/2022 10:34:58 PM
 *  Author: effic
 */ 


#ifndef DS1307_H_
#define DS1307_H_
#include "STD_MACROS.h"
#include "I2C.h"

#define  DS1307_ADDRESS 0b1101000
extern volatile uint8 date_counter;

void DS1307_read_time(volatile uint8 arr[]);
void DS1307_save_time(volatile uint8 arr[]);



#endif /* DS1307_H_ */