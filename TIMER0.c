/*
 * TIMER0.c
 *
 * Created: 9/3/2022 2:49:39 PM
 *  Author: effic
 */

#include "TIMER0.h"


void TIMER0_init_normal(uint8 prescalar) {
    TC0_CRA = 0;
    TC0_CRB = 0;
    //set prescalar
    TC0_CRB = (0x07 & prescalar);

    //clear counter register
    TC0_CNTR = 0;


    CLR_BIT(TC0_CRA, TC0_WGM0);
    CLR_BIT(TC0_CRA, TC0_WGM1);
    CLR_BIT(TC0_CRB, TC0_WGM2);


    //enable interrupt of timer over flow
    SET_BIT(SREG, 7);
    TC0_MSKR = 1 << TC0_OVF_IE;

}

void TIMER0_init_ctc_interrupt(uint8 prescalar, uint8 top_a, uint8 top_b) {
    //clear timer counter register
    TC0_CRA = 0;
    TC0_CRB = 0;
    TC0_CNTR = 0;

    //set prescalar
    TC0_CRB = (0x07 & prescalar);





    //select wave generation mode WGM3:0 = 1 0 0 0 = 4 mode = 4  (CTC mode)

    CLR_BIT(TC0_CRA, TC0_WGM0);
    SET_BIT(TC0_CRA, TC0_WGM1);
    CLR_BIT(TC0_CRB, TC0_WGM2);


    //set the top of CTC  and //toggle OC1A OC1B
    if (0 != top_a && 0 != top_b)
    {

        TC0_OCR_A = top_a;
        TC0_OCR_B = top_b;

        TC0_MSKR = (1 << TC0_OCB_IE) | (1 << TC0_OCA_IE);
    }
    else if (top_a != 0)
    {
        TC0_OCR_A = top_a;

        TC0_MSKR = (1 << TC0_OCA_IE);
    }
    else if (top_b != 0)
    {
        TC0_OCR_B = top_b;
        TC0_MSKR = (1 << TC0_OCB_IE);

    }



    //enable global interrupt
    SET_BIT(SREG, 7);

}


void TIMER0_init_ctc_pin(uint8 prescalar, uint8 top_a, uint8 top_b)
{
    //clear timer counter register
    TC0_CRA = 0;
    TC0_CRB = 0;
    TC0_CNTR = 0;




    //set the top of CTC  and //toggle OC1A OC1B
    if ((top_a != 0) && (top_b != 0))
    {
        TC0_OCR_A = top_a;
        TC0_OCR_B = top_b;
        TC0_CRA = (TC0_CRA & 0x0f) | (1 << TC0_COM_A0) | (1 << TC0_COM_B0);
        TC0_CRB = (1 << TC0_FOCA) | (1 << TC0_FOCB);



    }
    else if (top_a != 0)
    {
        TC0_OCR_A = top_a;
        TC0_CRA = (TC0_CRA & 0x0f) | (1 << TC0_COM_A0);
        TC0_CRB = (1 << TC0_FOCA);

    }
    else if (top_b != 0)
    {
        TC0_OCR_B = top_b;
        TC0_CRA = (TC0_CRA & 0x0f) | (1 << TC0_COM_B0);
        TC0_CRB = (1 << TC0_FOCB);
    }

    //select wave generation mode WGM3:0 = 1 0 0 0 = 4 mode = 4  (CTC mode)

    CLR_BIT(TC0_CRA, TC0_WGM0);
    SET_BIT(TC0_CRA, TC0_WGM1);
    CLR_BIT(TC0_CRB, TC0_WGM2);

    //set prescalar
    TC0_CRB = (0x07 & prescalar);

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

void TIMER0_init_fastPWM(uint8 prescalar, uint8 trig_a, uint8 trig_b, uint8 inverting_a, uint8 inverting_b)
{

    //clear timer counter register
	TC0_CRA= 0;
	TC0_CRB = 0;
    TC0_CNTR = 0;

    //set clock prescalar
    TC0_CRB = (TC0_CRB & 0xF8) | (0x07 & prescalar);
    TC0_OCR_A =  trig_a;
    TC0_OCR_B =  trig_b;
	//////////////////////////////////////////////////////////////////////////
	
    

    //////////////////////////////////////////////////////////////////////////
    //set non-inverting  or inverting

    if (0 != trig_a)
    {
        SET_BIT(TC0_CRA, TC0_COM_A0);
        SET_BIT(TC0_CRA, TC0_COM_A1);

        if (0 == inverting_a)  CLR_BIT(TC0_CRA, TC0_COM_A0);

    }

    if (0 != trig_b)
    {
        // initial is inverting mode
        SET_BIT(TC0_CRA, TC0_COM_B0);
        SET_BIT(TC0_CRA, TC0_COM_B1);

        if (0 == inverting_b)  CLR_BIT(TC0_CRA, TC0_COM_B0);

    }
    //////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////

    //select fast PWM mode 

    SET_BIT(TC0_CRA, TC0_WGM0);
    SET_BIT(TC0_CRA, TC0_WGM1);
    CLR_BIT(TC0_CRB, TC0_WGM2);
	//////////////////////////////////////////////////////////////////////////
   
    //disable all timer interrupts
    TC0_MSKR = 0;

}

/*******************************************************************************************************
function name:  TIMER0_init_phPWM

description  :initiating timer as phase correct PWM
arguments    :
              -prescalar -> prescalar of the clock.

              -trig     ->the value of the compare match.

             

return value: void

******************************************************************************************************/


void TIMER0_init_phPWM(uint8 prescalar, uint8 trig_a, uint8 trig_b, uint8 inverting_a, uint8 inverting_b)
{
    //////////////////////////////////////////////////////////////////////////
    //clear timer counter and control  registers
    TC0_CRA = 0;
    TC0_CRB = 0;
    TC0_CNTR = 0;

    
    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    //set the compare output match value
	TC0_OCR_A =  trig_a;
    TC0_OCR_B = trig_b;
    
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    //set non-inverting  or inverting 

    if (0 != trig_a)
    {
        // initial is inverting mode
        SET_BIT(TC0_CRA, TC0_COM_A0);
        SET_BIT(TC0_CRA, TC0_COM_A1);

        if (0 == inverting_a)  CLR_BIT(TC0_CRA, TC0_COM_A0);  //non inverting mode is select

    }


    if (0 != trig_b)
    {
        // initial is inverting mode
        SET_BIT(TC0_CRA, TC0_COM_B0);
        SET_BIT(TC0_CRA, TC0_COM_B1);

        if (0 == inverting_b)  CLR_BIT(TC0_CRA, TC0_COM_B0);  //non inverting mode is select

    }

    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    //select phase correct PWD mode
   
        SET_BIT(TC0_CRA, TC0_WGM0);
        CLR_BIT(TC0_CRA, TC0_WGM1);
        CLR_BIT(TC0_CRB, TC0_WGM2);
    //////////////////////////////////////////////////////////////////////////
    
	
	//set clock prescalar  to run the timer0
	TC0_CRB =  (0x07 & prescalar);
    //disable all timer interrupts
    TC0_MSKR = 0;

}


