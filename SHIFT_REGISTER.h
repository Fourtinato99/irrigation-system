/*
 * SHIFT_REGISTER.h
 *
 * Created: 8/20/2022 12:12:15 AM
 *  Author: effic
 */ 


#ifndef SHIFT_REGISTER_H_
#define SHIFT_REGISTER_H_
#include "STD_MACROS.h"

#define INIT_SHIFT_REGISTER (DDRD |=0b11100000)

#define DATA_PIN    PORTD5

#define LATCH_PIN   PORTD6
#define CLK_PIN     PORTD7


#define DATA_IN(x)  (  (x==1) ?   SET_BIT(PORTD,DATA_PIN)   :    CLR_BIT(PORTD,DATA_PIN)    )
#define CLK_IN(x)   (  (x==1) ?   SET_BIT(PORTD,CLK_PIN)    :    CLR_BIT(PORTD,CLK_PIN)     )
#define LATCH_IN(x) (  (x==1) ?   SET_BIT(PORTD,LATCH_PIN)  :    CLR_BIT(PORTD,LATCH_PIN)   )

void SHIFT_REGISTER_init(void);


void SHIFT_REGISTER_OUT(uint8_t data);





#endif /* SHIFT_REGISTER_H_ */