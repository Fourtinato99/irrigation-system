/*
 * SHIFT_REGISTER.c
 *
 * Created: 8/20/2022 12:12:28 AM
 *  Author: effic
 */ 

#include "SHIFT_REGISTER.h"


void SHIFT_REGISTER_init(void){
	INIT_SHIFT_REGISTER ;
}
void SHIFT_REGISTER_OUT(uint8_t data){
	
	LATCH_IN(0);
	
	for(uint8_t i =0 ; i< 8 ;i++){
		CLK_IN(0);
		
		DATA_IN(  ((data>>(7-i)) & 1));
		
		CLK_IN(1);
		
	}
	
	LATCH_IN(1);
}