/*
 * adc.c
 *
 * Created: 4/20/2018 7:14:29 PM
 *  Author: Ahmed Nasr
 */ 

#include "adc.h"

#include "stdint_macro.h"




void ADC_init()
{
	SETBIT(ADMUX,6);
	CLRBIT(ADMUX,7);
	SETBIT(ADCSRA,7);
	SETBIT(ADCSRA,0);
	SETBIT(ADCSRA,1);
	SETBIT(ADCSRA,2);
	
	
}

uint16_t ADC_read(uint8_t channel)
{
	
	SETBIT(ADCSRA,6);
	while(READBIT(ADCSRA,6) == 1)  {}
	
	 ;
		
	return( ADCL | ADCH<<8);
}