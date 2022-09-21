/*
 * INTERRUPT.h
 *
 * Created: 8/22/2022 10:15:08 PM
 *  Author: effic
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "STD_MACROS.h"
#include <avr/interrupt.h>
#define MCUCR_328P *((volatile uint8*)0x55)  //MCU control register

//external interrupt
#define EICRA_328P *((volatile uint8*)0x69) //external interrupt control register A
#define EIMSK_328P *((volatile uint8*)0x3D)  //external interrupt mask register

#define INT0_328P *((volatile  uint16*)0x02)
#define INT1_328P *((volatile  uint16*)0x04)



//pin change interrupt
#define PCICR_328P *((volatile uint8*)0x068)  //pin change interrupt control register
#define PCMSK0_328P *((volatile uint8*)0x6B)  //pin change mask 0 register of vector PCINT0
#define PCMSK1_328P *((volatile uint8*)0x6C)  //pin change mask 0 register of vector PCINT1
#define PCMSK2_328P *((volatile uint8*)0x6D)  //pin change mask 0 register of vector PCINT1




void INTERRUPT_EX_init(uint8 int_num , uint8 mode   );
void INTERRUPT_PC_init( uint8 pin);




#endif /* INTERRUPT_H_ */