/*
 * UTILITIES.h
 *
 * Created: 8/22/2022 10:12:04 PM
 *  Author: effic
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "STD_MACROS.h"
#include "LCD.h"
#include "EEPROM.h"
#include "INTERRUPT.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>

extern volatile uint8 set_time_mode;
extern volatile uint8 selector;
extern volatile uint8 time_mode_flag;
extern volatile uint8 timer_flag;
extern volatile uint8 manual_flag;
extern volatile timerUp timers;
extern volatile uint8 set_timers_mode ;
extern volatile uint32 timer_properties;
extern volatile uint8 timer_number ;       //number of existing timers
extern volatile uint8 propery_changer ;
extern volatile uint8 timer_changer ;
extern volatile timerUp timers;

extern volatile uint8 DS_time[7];
extern volatile uint8 running_timers;
 

//////////////////////////////////////////////////////////////////////////
// button defines
#define SET_TIME_BT  3
#define SET_TIMER_BT 2
#define MANUAL_BT    1

#define UP_BT        0
#define DOWN_BT      5
#define RIGHT_BT     4
#define  OK_BT       3



void UTILITY_delay_ms(uint16 second);

void UTILITY_init_button(void);

void UTILITY_display_time (volatile uint8 DS_time[]);
void UTILITY_display_timer(void);
void UTILITY_display_edit_timer(void);
void UTILITY_display_manual(volatile uint8 running_timers_temp);


void UTILITY_get_running_timers(void);
void UTILITy_save_timer(void);
void UTILITy_remove_timer(void);
void UTILITY_running_or_not(void);
uint32 UTILITY_get_bits(volatile uint32 *var,uint8 num ,uint8 bit);


#endif /* UTILITIES_H_ */