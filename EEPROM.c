/*
 * EEPROM.c
 *
 * Created: 8/19/2022 7:11:30 PM
 *  Author: effic
 */ 

#include "EEPROM.h"


void EEPROM_write_8(uint16_t address , uint8_t data){
	
	while(WRITING_DONE);
	PUT_DATA(data);
	PUT_ADDRESS(address);
	REAY_TO_WRITE;
	START_WRITING;
	
	while(WRITING_DONE);
}

void EEPROM_write_16(uint16_t address , uint16_t data){
	EEPROM_write_8(address  ,  data );
	data>>=8;
	EEPROM_write_8(address+1,  data );
}

void EEPROM_write_32(uint16_t address , uint32_t data){
	EEPROM_write_8(address  ,  data );
	data>>=8;
	EEPROM_write_8(address+1,  data );
	data>>=8;
	EEPROM_write_8(address+2,  data );
	data>>=8;
	EEPROM_write_8(address+3,  data );
}

void EEPROM_write_64(uint16_t address , uint64_t data){
	
	EEPROM_write_8(address  ,  data );
	data>>=8;
	EEPROM_write_8(address+1,  data );
	data>>=8;
	EEPROM_write_8(address+2,  data );
	data>>=8;
	EEPROM_write_8(address+3,  data );
	data>>=8;
	EEPROM_write_8(address+4,  data );
	data>>=8;
	EEPROM_write_8(address+5,  data );
	data>>=8;
	EEPROM_write_8(address+6,  data );
	data>>=8;
	EEPROM_write_8(address+7,  data );
}






uint8_t EEPROM_read_8(uint16_t address){
	PUT_ADDRESS(address);
	START_READ;
	return GET_DATA ;
}


uint16_t EEPROM_read_16(uint16_t address){
	uint16_t temp = 0;
	temp =  EEPROM_read_8(address+1) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address) ;
	return temp;
}

uint32_t EEPROM_read_32(uint16_t address){
	uint32_t temp = 0;
	temp =  EEPROM_read_8(address+3) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+2) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+1) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address  ) ;  
	return temp;
	
}

uint64_t EEPROM_read_64(uint16_t address){
	uint64_t temp = 0;
	temp =  EEPROM_read_8(address+7) ;
	temp <<= 8;
	temp =  EEPROM_read_8(address+6) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+5) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+4) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+3) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+2) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address+1) ;
	temp <<= 8;
	temp |=  EEPROM_read_8(address  ) ;
	
	return temp;
	
}