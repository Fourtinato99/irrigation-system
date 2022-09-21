/*
 * STD_MACROS.h
 *
 * Created: 8/16/2022 11:38:55 PM
 *  Author: effic
 */


#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#define F_CPU 8000000LL

#include <avr/io.h>
#include <util/delay.h>


typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;


typedef  char       int8;
typedef  short      int16;
typedef  long       int32;
typedef  long long  int64;

typedef struct {
	
	uint64 lower;
	uint64 upper;
	
}all;

typedef struct {

	uint32 timer1 : 1;
	uint32 timer2 : 1;
	uint32 timer3 : 1;
	uint32 timer4 : 1;
	uint32 timer5 : 1;
	uint32 timer6 : 1;
	uint32 timer7 : 1;
	uint32 timer8 : 1;



	uint32 day1 : 1;
	uint32 day2 : 1;
	uint32 day3 : 1;
	uint32 day4 : 1;
	uint32 day5 : 1;
	uint32 day6 : 1;
	uint32 day7 : 1;
	uint32 on_off : 1;
	
	uint32 period_minutes : 6;
	uint32 period_hours   : 5;

	uint32 start_minutes  : 6;
	uint32 start_hours    : 5;
}timerSp;

typedef union
{
	uint64 timer;
	timerSp timer_properties;
}timerUp;


#define SET_BIT(REG , BIT)(REG |= (1<<BIT))
#define CLR_BIT(REG , BIT)(REG &= ~(1<<BIT))
#define TOG_BIT(REG , BIT)(REG ^= (1<<BIT))
#define READ_BIT(REG,BIT)((REG >> BIT) & 1)











#endif /* STD_MACROS_H_ */