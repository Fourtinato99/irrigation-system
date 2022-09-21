/*
 * INTERRUPT.c
 *
 * Created: 8/22/2022 10:15:40 PM
 *  Author: effic
 */ 

#include "INTERRUPT.h"
#include "STD_MACROS.h"

void INTERRUPT_EX_init(uint8 int_num , uint8 mode  ){
	
    //enable the interrupt
	SET_BIT(SREG , 7);
    SET_BIT(EIMSK_328P, (int_num) );
	
	//set mode
	((mode & 1) == 1) ? SET_BIT(EICRA_328P, (0+2*int_num) ) : CLR_BIT(EICRA_328P, (0+2*int_num) );
	((mode & 2) == 2) ? SET_BIT(EICRA_328P, (1+2*int_num) ) : CLR_BIT(EICRA_328P, (1+2*int_num) );
	
	
	

}

void INTERRUPT_PC_init( uint8 pin){
	uint8 int_vector =pin/8;
	uint8 pin_mask = pin%8;
	SET_BIT(PCICR_328P, int_vector );
	
	 int_vector == 0 ? SET_BIT(PCMSK0_328P,pin_mask ) : (  int_vector == 1  ? SET_BIT(PCMSK1_328P,pin_mask ) :SET_BIT(PCMSK2_328P,pin_mask )  );
	SET_BIT(SREG , 7);
}

