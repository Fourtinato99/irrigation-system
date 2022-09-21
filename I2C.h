/*
 * I2C.h
 *
 * Created: 8/28/2022 12:42:32 PM
 *  Author: effic
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "STD_MACROS.h"


//define register of i2c module in atmega328p
#define I2C_BR *((volatile uint8*) 0xB8)
#define I2C_DR *((volatile uint8*) 0xBB)
#define I2C_AR *((volatile uint8*) 0xBA)
#define I2C_CR *((volatile uint8*) 0xBC)
#define I2C_SR *((volatile uint8*) 0xB9)

//define the number of bits 

#define PRES0 0
#define PRES1 1

#define I2C_IFL  7
#define I2C_EAC  6
#define I2C_STR  5
#define I2C_STO  4
#define I2C_WCF  3
#define I2C_ENB  2
#define I2C_IEN  0

void I2C_master_init(uint8 address);
void I2C_master_start(void);
void I2C_master_restart(void);
void I2C_master_stop(void);
void I2C_master_send_A_R(uint8 address);
void I2C_master_send_A_W(uint8 address);
void I2C_master_send_D(uint8 data);
uint8 I2C_master_recieve(uint8 xck);



void I2C_slave_init(uint8 address);
uint8 I2C_slave_lisen(void);
void I2C_slave_send(uint8 data);
uint8 I2C_slave_recieve(void);



#endif /* I2C_H_ */