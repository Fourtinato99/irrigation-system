/*
 * TIMER0.h
 *
 * Created: 9/3/2022 2:49:25 PM
 *  Author: effic
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "STD_MACROS.h"

//define timer 0 registers


// TCCR1A => timer/counter1 control register A and its bits
#define TC0_CRA *((volatile uint8*)0x44 )
#define TC0_COM_A1 7
#define TC0_COM_A0 6

#define TC0_COM_B1 5
#define TC0_COM_B0 4

#define TC0_WGM1 1
#define TC0_WGM0 0

// TCCR0B => timer/counter0 control register B and its bits
#define  TC0_CRB *((volatile uint8*) 0x45)

#define TC0_FOCA 7  //Force Output Compare for Channel A
#define TC0_FOCB 6  //Force Output Compare for Channel B


#define TC0_WGM2 3

#define TC0_CS2 2
#define TC0_CS1 1
#define TC0_CS0 0



//TIMSK1  Timer/Counter1 Interrupt Mask Register
#define TC0_MSKR *((volatile uint8*)0x6E)
#define TC0_OVF_IE  0
#define TC0_OCA_IE 1
#define TC0_OCB_IE 2



//  TCNT0 timer/counter counter register
#define  TC0_CNTR *((volatile uint8*) 0x46 )

//OCR0A  Output Compare Register 0 A
#define TC0_OCR_A *((volatile uint8*) 0x47)

// OCR0B   Output Compare Register 0 B
#define TC0_OCR_B *((volatile uint8*)0x48)




// functions
void TIMER0_init_normal(uint8 prescalar);
void TIMER0_init_ctc_interrupt(uint8 prescalar,uint8 top_a ,uint8 top_b );
void TIMER0_init_ctc_pin(uint8 prescalar,uint8 top_a ,uint8 top_b );
void TIMER0_init_fastPWM(uint8 prescalar,uint8 trig_a,uint8 trig_b, uint8 inverting_a , uint8 inverting_b );
void TIMER0_init_phPWM(uint8 prescalar,uint8 trig_a,uint8 trig_b, uint8 inverting_a , uint8 inverting_b );


//







#endif /* TIMER0_H_ */