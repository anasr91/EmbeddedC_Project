/*
 * pwm.c
 *
 * Created: 4/20/2018 7:13:39 AM
 *  Author: Ahmed Nasr
 */ 
#ifndef STDINT_MACRO_H_
#define STDINT_MACRO_H_


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define SETBIT(PORT,PIN)    (PORT|=(1<<PIN))
#define TOGBIT(PORT,PIN) (PORT^=(1<<PIN))
#define CLRBIT(PORT,PIN)  (PORT&=~(1<<PIN))
#define READBIT(PORT,PIN)   (PORT&(1<<PIN))
#define CHECKPIN(PORT,PIN)  (1&(PORT>>PIN))



#endif /* STDINT_MACRO_H_ */