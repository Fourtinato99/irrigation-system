/*
 * TIMER1.c
 *
 * Created: 9/1/2022 1:01:10 AM
 *  Author: effic
 */ 
#include "TIMER1.h"


void TIMER1_init_normal(uint8 prescalar){
		TC1_CRA = 0;
		TC1_CRB = 0;
	//set prescalar
	TC1_CRB = (TC1_CRB & 0xF8)|(0x07 & prescalar);
	
	//clear counter register
	TC1_CNTR = 0;
	
	//select waveform generator mode :normal mode WGM0,1,2,3 = 0 0 0 0
	//TC1_CRA = ( TC1_CRA & 0xFC); // TC1_CRA & 0xFC % 0b1111 1100
	//TC1_CRB = ( TC1_CRA & 0xE7) ; // TC1_CRB & 0xFC % 0b1110 0111
	CLR_BIT(TC1_CRA,TC1_WGM0);
	CLR_BIT(TC1_CRA,TC1_WGM1);
	CLR_BIT(TC1_CRB,TC1_WGM2);
	CLR_BIT(TC1_CRB,TC1_WGM3);
	
	//enable interrupt of timer over flow
	SET_BIT(SREG,7);
	TC1_MSKR = 0x01;
	
}

void TIMER1_init_ctc_interrupt(uint8 prescalar,uint16 top_a ,uint16 top_b ){
	//clear timer counter register
	TC1_CRA = 0;
	TC1_CRB = 0;
	TC1_CNTR = 0;
	
	//set prescalar
	TC1_CRB = (0x07 & prescalar);
	
	
	

	
	//select wave generation mode WGM3:0 = 1 0 0 0 = 4 mode = 4  (CTC mode)

	CLR_BIT(TC1_CRA,TC1_WGM0);
	CLR_BIT(TC1_CRA,TC1_WGM1);
	SET_BIT(TC1_CRB,TC1_WGM2);
	CLR_BIT(TC1_CRB,TC1_WGM3);

	//set the top of CTC  and //toggle OC1A OC1B
	if(0 != top_a && 0 != top_b )
	{	
		 
		TC1_OCR_A = top_a;
		TC1_OCR_B = top_b;
		
		TC1_MSKR = (1<<TC1_OCB_IE) | (1<<TC1_OCA_IE);
	}
	else if(top_a !=  0)
	{ 
		TC1_OCR_A = top_a;
		
		TC1_MSKR =  (1<<TC1_OCA_IE);
	}
	else if(top_b !=  0)
	{
		TC1_OCR_B = top_b;
		TC1_MSKR = (1<<TC1_OCB_IE) ;
		
	}
	
	
	
	//enable global interrupt
	SET_BIT(SREG,7);
	
}


void TIMER1_init_ctc_pin(uint8 prescalar,uint16 top_a ,uint16 top_b )
{
	//clear timer counter register
	TC1_CRA = 0;
	TC1_CRB = 0;
	TC1_CNTR = 0;
	
	//set prescalar
	TC1_CRB =  (0x07 & prescalar);

	
	//set the top of CTC  and //toggle OC1A OC1B
	if( (top_a != 0)  &&  (top_b != 0) )
	{
		TC1_OCR_A = top_a;
		TC1_OCR_B = top_b;
		TC1_CRA = (TC1_CRA & 0x0f) | (1<<TC1_COM_A0) | (1<<TC1_COM_B0);
		TC1_CRC = (1<<TC1_FOCA) | (1<<TC1_FOCB);
		
		
		
	}
	else if(top_a !=  0)
	{
		TC1_OCR_A = top_a;
		TC1_CRA = (TC1_CRA & 0x0f) | (1<<TC1_COM_A0);
		TC1_CRC = (1<<TC1_FOCA);
		
	}
	else if(top_b !=  0)
	{
		TC1_OCR_B = top_b;
		TC1_CRA = (TC1_CRA & 0x0f) | (1<<TC1_COM_B0);
		TC1_CRC =  (1<<TC1_FOCB);
	}
	
	//select wave generation mode WGM3:0 = 1 0 0 0 = 4 mode = 4  (CTC mode)

	CLR_BIT(TC1_CRA,TC1_WGM0);
	CLR_BIT(TC1_CRA,TC1_WGM1);
	SET_BIT(TC1_CRB,TC1_WGM2);
	CLR_BIT(TC1_CRB,TC1_WGM3);
	
	
}




/*******************************************************************************************************
function name:  TIMER1_init_fastPWM

description  :initiating timer as fast PWM
arguments    :
			  prescalar -> prescalar of the clock
			  trig     ->the value of the compare match
			  num_bits  -> number of bits that determines the top value of the counter (8,9,10)bits
			             8-bits  = 0x00FF   top=>255
						 9-bits  = 0x01FF   top=>511
						 10-bits = 0x03FF   top=>1023

return value: void

******************************************************************************************************/

void TIMER1_init_fastPWM(uint8 prescalar,uint16 trig_a,uint16 trig_b, uint8 inverting_a , uint8 inverting_b , uint8 num_bits)
{
	
	//clear timer counter register
	TC1_CNTR =0;
	
	//set clock prescalar
	TC1_CRB = (TC1_CRB & 0xF8) | (0x07 & prescalar);
	
	//set the compare output match value
	if(0 != trig_a && 0 != trig_b)
	{
		TC1_OCR_A = (3 << (num_bits-2) | 0x00FF ) & trig_a ;
		TC1_OCR_B = (3 << (num_bits-2) | 0x00FF ) & trig_b ;
	}
	else if (0 != trig_a)
	{
		TC1_OCR_A = (3 << (num_bits-2) | 0x00FF ) & trig_a ;
	}
	else if(0 != trig_b)
	{
		TC1_OCR_A = (3 << (num_bits-2) | 0x00FF ) & trig_b ;
	}
		
	
	
	//set non-inverting  or inverting
	
	if( 0 != trig_a )
	{
		SET_BIT(TC1_CRA,TC1_COM_A0);
		SET_BIT(TC1_CRA,TC1_COM_A1);

		if(0 == inverting_a)  CLR_BIT(TC1_CRA,TC1_COM_A0);
		
	}
	
	
	if( 0 != trig_b )
	{
		// initial is inverting mode
		SET_BIT(TC1_CRA,TC1_COM_B0);  
		SET_BIT(TC1_CRA,TC1_COM_B1);

		if(0 == inverting_b)  CLR_BIT(TC1_CRA,TC1_COM_B0);
			
	}
	
	
	//select fast PWM mode 
	if(8 == num_bits)
	{
		SET_BIT(TC1_CRA,TC1_WGM0);
		CLR_BIT(TC1_CRA,TC1_WGM1);
		SET_BIT(TC1_CRB,TC1_WGM2);
		CLR_BIT(TC1_CRB,TC1_WGM3);
		
	}
	else if (9 == num_bits)
	{
		CLR_BIT(TC1_CRA,TC1_WGM0);
		SET_BIT(TC1_CRA,TC1_WGM1);
		SET_BIT(TC1_CRB,TC1_WGM2);
		CLR_BIT(TC1_CRB,TC1_WGM3);
		
	}
	else
	{
		SET_BIT(TC1_CRA,TC1_WGM0);
		SET_BIT(TC1_CRA,TC1_WGM1);
		SET_BIT(TC1_CRB,TC1_WGM2);
		CLR_BIT(TC1_CRB,TC1_WGM3);
	}
	
	//disable all timer interrupts
	TC1_MSKR = 0;
	
}

/*******************************************************************************************************
function name:  TIMER1_init_phPWM

description  :initiating timer as phase correct PWM
arguments    :
			  -prescalar -> prescalar of the clock.
			  
			  -trig     ->the value of the compare match.
			  
			  -num_bits  -> number of bits that determines the top value of the counter (8,9,10)bits
			             8-bits  = 0x00FF   top=>255
						 9-bits  = 0x01FF   top=>511
						 10-bits = 0x03FF   top=>1023

return value: void

******************************************************************************************************/


void TIMER1_init_phPWM(uint8 prescalar,uint16 trig_a,uint16 trig_b, uint8 inverting_a , uint8 inverting_b , uint8 num_bits)
{
	//////////////////////////////////////////////////////////////////////////
	//clear timer counter and control  registers
	TC1_CRA = 0;
	TC1_CRB = 0;
	TC1_CNTR =0;
	
	//set clock prescalar
	TC1_CRB = (TC1_CRB & 0xF8) | (0x07 & prescalar);
	//////////////////////////////////////////////////////////////////////////
	
	
    //////////////////////////////////////////////////////////////////////////
    //set the compare output match value
    if(0 != trig_a && 0 != trig_b)
    {
	    TC1_OCR_A = (3 << (num_bits-2) | 0x00FF ) & trig_a ;
	    TC1_OCR_B = (3 << (num_bits-2) | 0x00FF ) & trig_b ;
    }
    else if (0 != trig_a)
    {
	    TC1_OCR_A = (3 << (num_bits-2) | 0x00FF ) & trig_a ;
    }
    else if(0 != trig_b)
    {
	    TC1_OCR_A = (3 << (num_bits-2) | 0x00FF ) & trig_b ;
    }
	//////////////////////////////////////////////////////////////////////////
	
    
    
    //////////////////////////////////////////////////////////////////////////
    //set non-inverting  or inverting 
    
    if( 0 != trig_a )
    {
		// initial is inverting mode
	    SET_BIT(TC1_CRA,TC1_COM_A0);
	    SET_BIT(TC1_CRA,TC1_COM_A1);

	    if(0 == inverting_a)  CLR_BIT(TC1_CRA,TC1_COM_A0);  //non inverting mode is select
	    
    }
    
    
    if( 0 != trig_b )
    {
	    // initial is inverting mode
	    SET_BIT(TC1_CRA,TC1_COM_B0);
	    SET_BIT(TC1_CRA,TC1_COM_B1);

	    if(0 == inverting_b)  CLR_BIT(TC1_CRA,TC1_COM_B0);  //non inverting mode is select
	    
    }
	
	//////////////////////////////////////////////////////////////////////////
    

	
	//////////////////////////////////////////////////////////////////////////
	//select fast PWD mode
	if(8 == num_bits){
		SET_BIT(TC1_CRA,TC1_WGM0);
		CLR_BIT(TC1_CRA,TC1_WGM1);
		CLR_BIT(TC1_CRB,TC1_WGM2);
		CLR_BIT(TC1_CRB,TC1_WGM3);
		
	}
	else if (9 == num_bits)
	{
		CLR_BIT(TC1_CRA,TC1_WGM0);
		SET_BIT(TC1_CRA,TC1_WGM1);
		CLR_BIT(TC1_CRB,TC1_WGM2);
		CLR_BIT(TC1_CRB,TC1_WGM3);
		
	}
	else
	{
		SET_BIT(TC1_CRA,TC1_WGM0);
		SET_BIT(TC1_CRA,TC1_WGM1);
		CLR_BIT(TC1_CRB,TC1_WGM2);
		CLR_BIT(TC1_CRB,TC1_WGM3);
	}
	//////////////////////////////////////////////////////////////////////////
	
	//disable all timer interrupts
	TC1_MSKR = 0;
	
}


void TIMER1_init_input_cap(uint8 presaclar)
{
	
	TC1_CRA  = 0;
	TC1_CRB  = 0;
	TC1_CRC  = 0;
	TC1_CNTR = 0;
	
	//set the prescalar
	TC1_CRB = 0x07 & presaclar;
	//set the timer mode to normal mode WGM3:0 = 0 
	CLR_BIT(TC1_CRA,TC1_WGM0);
	CLR_BIT(TC1_CRA,TC1_WGM1);
	CLR_BIT(TC1_CRB,TC1_WGM2);
	CLR_BIT(TC1_CRB,TC1_WGM3);
	
	//rising edge detector
	SET_BIT(TC1_CRB,TC1_ICES);
	
	//enable the overflow interrupt and input capture interrupt
	TC1_MSKR = (1<<TC1_OVF_IE) | (1<<TC1_IC_IE);
	SET_BIT(SREG,7);   //enable global interrupt
	
	
	
	
}