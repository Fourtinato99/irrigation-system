/*
 * DS1307.c
 *
 * Created: 9/14/2022 10:36:48 PM
 *  Author: effic
 */ 


#include "DS1307.h"
#include "LCD.h"

void DS1307_read_time(volatile uint8 arr[]){
	
	
	
	//first read from DS1307 as BCD format
	I2C_master_start();
	I2C_master_send_A_W(DS1307_ADDRESS);
	I2C_master_send_D(0x00);
	I2C_master_restart();
	I2C_master_send_A_R(DS1307_ADDRESS);
	arr[0] = I2C_master_recieve(1);     //seconds
	arr[1] = I2C_master_recieve(1);		//minutes
	arr[2] = I2C_master_recieve(1);		//hours
	arr[3] = I2C_master_recieve(1);		//days
	arr[4] = I2C_master_recieve(1);		//date
	arr[5] = I2C_master_recieve(1);		//months
	arr[6] = I2C_master_recieve(1);		//yeas
	
	I2C_master_stop();
	
	
	//then convert BCD to binary
	arr[0] = (arr[0] >> 4) * 10 + (arr[0] & 0x0f);   //seconds
	arr[1] = (arr[1] >> 4) * 10 + (arr[1] & 0x0f);   //minutes
	arr[2] = (arr[2] >> 4) * 10 + (arr[2] & 0x0f);   //hours
	
	arr[4] = (arr[4] >> 4) * 10 + (arr[4] & 0x0f);    //date
	arr[5] = (arr[5] >> 4) * 10 + (arr[5] & 0x0f);    //months
	arr[6] = (arr[6] >> 4) * 10 + (arr[6] & 0x0f);    //years

	
}


void DS1307_save_time(volatile uint8 arr[])
{
	
	//first convert binary to BCB
	date_counter = arr[4];
	
	arr[0] =( (arr[0] / 10 ) << 4) | (arr[0] % 10 );
	arr[1] =( (arr[1] / 10 ) << 4) | (arr[1] % 10 );
	arr[2] =( (arr[2] / 10 ) << 4) | (arr[2] % 10 );
	
	arr[4] =( (arr[4] / 10 ) << 4) | (arr[4] % 10 );
	arr[5] =( (arr[5] / 10 ) << 4) | (arr[5] % 10 );
	arr[6] =( (arr[6] / 10 ) << 4) | (arr[6] % 10 );
	
	//then save to DS1307 ic
	
	I2C_master_start();
	I2C_master_send_A_W(DS1307_ADDRESS);
	I2C_master_send_D(0x00);
	I2C_master_send_D( arr[0]);
	I2C_master_send_D( arr[1]);
	I2C_master_send_D( arr[2]);
	
	I2C_master_send_D( arr[3]);
	
	I2C_master_send_D( arr[4]);
	I2C_master_send_D( arr[5]);
	I2C_master_send_D( arr[6]);
	I2C_master_stop();
	
}