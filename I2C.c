 /*
 * I2C.c
 *
 * Created: 8/28/2022 12:42:50 PM
 *  Author: effic
 */ 

#include "I2C.h"
#include "LCD.h"


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//              master functions

void I2C_master_init(uint8 address){
	I2C_CR = (1<<I2C_ENB);
	I2C_AR =(address<<1 | 0x01);   //initiating the slave address and enable general call recognition
	I2C_BR = 0x32;                 // initiating the bit rate =  100k  , with zero prescalar
	I2C_SR = 0x00;                 // initiating prescalar to zero
	I2C_CR = (1<<I2C_ENB)|(1<<I2C_EAC);
	
}



// sending start condition
void I2C_master_start(void){
	
	I2C_CR = (1<<I2C_IFL)|(1<<I2C_STR)|(1<<I2C_ENB);
	
	while((I2C_CR & (1<<I2C_IFL)) == 0);
	while(0)
	{
		
		
		if(I2C_SR == 0x08) return;
	}
}

// sending repeating start condition
void I2C_master_restart(void){
	
	while(1)
	{
		I2C_CR = (1<<I2C_IFL)|(1<<I2C_STR)|(1<<I2C_ENB);
		while((I2C_CR & (1<<I2C_IFL)) == 0);
		
		if(I2C_SR == 0x10) return;
		
	}
}


//sending stop condition
void I2C_master_stop(void){
	I2C_CR = (1<<I2C_IFL)|(1<<I2C_STO)|(1<<I2C_ENB);
}

void I2C_master_send_A_W(uint8 address){
	
	while(1)
	{
		I2C_DR = address<<1 ;
		I2C_CR = (1<<I2C_IFL) | (1<<I2C_ENB) ;
		while ( (I2C_CR & (1<<I2C_IFL)) == 0);
	    if(I2C_SR == 0x18) 
		return;
	}
	
}

void I2C_master_send_A_R(uint8 address){
	
	while(1)
	{
		I2C_DR = ((address<<1) | 1) ;
		I2C_CR = (1<<I2C_IFL) | (1<<I2C_ENB) ;
		while ( (I2C_CR & (1<<I2C_IFL)) == 0);
		if(I2C_SR == 0x40) return;
	}
	
}

void I2C_master_send_D(uint8 data){
	
	while(1)
	{
		I2C_DR = data ;
		I2C_CR = (1<<I2C_IFL) | (1<<I2C_ENB);
		while (  0 == (I2C_CR & (1<<I2C_IFL)));	
		if(0x28 == I2C_SR ) return;
	}
	
}

uint8 I2C_master_recieve(uint8 xck){
	
	while(1)
	{
		I2C_CR = (1<<I2C_IFL) | (1<<I2C_ENB)|(xck<<I2C_EAC);
		while ( (I2C_CR & (1<<I2C_IFL)) == 0);
		if(0x50 == I2C_SR ) return I2C_DR;
	}
	
	
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//       slave functions


void I2C_slave_init(uint8 address){
	I2C_CR = (1<<I2C_ENB);
	I2C_AR =(address<<1 | 0x01);                              //initiating the slave address and enable general call recognition
	                                        
	I2C_CR = (1<<I2C_ENB)|(1<<I2C_EAC)|(I2C_IFL) ;
	
}


uint8 I2C_slave_lisen(void){
	while(1)
	{
		
		while( (I2C_CR & (1<< I2C_IFL)) == 0 );
		if (I2C_SR ==  0x60) return 0;  //slave will receive
		if (I2C_SR ==  0xA8) return 1;  //slave will send
	}
	
}

void I2C_slave_send(uint8 data){
	
	while(1){
		I2C_DR = data ;
		I2C_CR = (1<<I2C_ENB)|(1<<I2C_IFL)|(1<<I2C_EAC);
		while ( (I2C_CR & (1<<I2C_IFL)) == 0);
		
		if(I2C_SR == 0xB8)return;
		
		
	}
	
}

uint8 I2C_slave_recieve(void){
	
	while (1)
	{
		I2C_CR = (1<<I2C_EAC) | (1<<I2C_ENB) | (1<<I2C_IFL);
		while ( (I2C_CR & (1<<I2C_IFL)) == 0);
		if(I2C_SR ==0x80 )
		return I2C_DR;
		
	}
	
	
}