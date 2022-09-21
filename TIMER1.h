/*
 * TIMER1.h
 *
 * Created: 8/31/2022 11:56:26 PM
 *  Author: effic
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_
#include "STD_MACROS.h"

//define timer 1 registers


// TCCR1A => timer/counter1 control register A and its bits
#define TC1_CRA *((volatile uint8*)0x80 )
#define TC1_COM_A1 7
#define TC1_COM_A0 6

#define TC1_COM_B1 5
#define TC1_COM_B0 4

#define TC1_WGM1 1
#define TC1_WGM0 0

// TCCR1B => timer/counter1 control register B and its bits
#define  TC1_CRB *((volatile uint8*) 0x81)

#define TC1_ICNC 7  //ICNC1: Input Capture Noise Canceler
#define TC1_ICES 6   // rising or falling edge detector

#define TC1_WGM3 4
#define TC1_WGM2 3

#define TC1_CS2 2
#define TC1_CS1 1
#define TC1_CS0 0

// TCCR1C => timer/counter1 control register C and its bits
#define  TC1_CRC *((volatile uint8*)0x82 )

#define TC1_FOCA 7  //Force Output Compare for Channel A
#define TC1_FOCB 6  //Force Output Compare for Channel B

//TIMSK1  Timer/Counter1 Interrupt Mask Register
#define TC1_MSKR *((volatile uint8*)0x6F)
#define TC1_OVF_IE  0   //Timer/Counter1, Overflow Interrupt Enable
#define TC1_OCA_IE 1    //Timer/Counter1, Output Compare A Match Interrupt Enable
#define TC1_OCB_IE 2    //Timer/Counter1, Output Compare B Match Interrupt Enable
#define TC1_IC_IE 5     //Timer/Counter1, Input Capture Interrupt Enable


//  TCNT1H and TCNT1L timer/counter counter register 
#define  TC1_CNTR *((volatile uint16*) 0x84 )
  

//OCR1AH and OCR1AL  Output Compare Register 1 A
#define TC1_OCR_A *((volatile uint16*) 0x88)

// OCR1BH and OCR1BL  Output Compare Register 1 B
#define TC1_OCR_B *((volatile uint16*)0x8A)

// ICR1H and ICR1L  Input Capture Register 1
#define TC1_ICR *((volatile uint16*) 0x86)




// functions
void TIMER1_init_normal(uint8 prescalar);
void TIMER1_init_ctc_interrupt(uint8 prescalar,uint16 top_a ,uint16 top_b );
void TIMER1_init_ctc_pin(uint8 prescalar,uint16 top_a ,uint16 top_b );
void TIMER1_init_fastPWM(uint8 prescalar,uint16 trig_a,uint16 trig_b, uint8 inverting_a , uint8 inverting_b , uint8 num_bits);
void TIMER1_init_phPWM(uint8 prescalar,uint16 trig_a,uint16 trig_b, uint8 inverting_a , uint8 inverting_b , uint8 num_bits);
void TIMER1_init_input_cap(uint8 presaclar);

//






#endif /* TIMER1_H_ */