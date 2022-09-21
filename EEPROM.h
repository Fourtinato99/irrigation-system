/*
 * EEPROM.h
 *
 * Created: 8/19/2022 7:11:12 PM
 *  Author: effic
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "STD_MACROS.h"


#define REAY_TO_WRITE SET_BIT(EECR,EEMPE)

#define START_WRITING SET_BIT(EECR,EEPE)

#define START_READ SET_BIT(EECR ,EERE)

#define WRITING_DONE READ_BIT(EECR,EEPE)

#define PUT_DATA(x) (EEDR = x)

#define PUT_ADDRESS(x) (EEAR = x)

#define GET_DATA EEDR




void EEPROM_write_8(uint16_t address , uint8_t data);
void EEPROM_write_16(uint16_t address , uint16_t data);
void EEPROM_write_32(uint16_t address , uint32_t data);
void EEPROM_write_64(uint16_t address , uint64_t data);

uint8_t EEPROM_read_8(uint16_t address);
uint16_t EEPROM_read_16(uint16_t address);
uint32_t EEPROM_read_32(uint16_t address);
uint64_t EEPROM_read_64(uint16_t address);



#endif /* EEPROM_H_ */