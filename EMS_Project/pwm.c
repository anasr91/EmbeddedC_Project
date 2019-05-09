/*
 * pwm.c
 *
 * Created: 4/20/2018 7:13:39 AM
 *  Author: Ahmed Nasr
 */ 
#include "pwm.h"
#include "stdint_macro.h"

void PWM1_OCR1A_init()
{
	
	SETBIT(DDRD,4);  // OCR1A
	
	SETBIT(DDRD,5);

	
	//CLRBIT(TCCR1A,COM1A0);
	SETBIT(TCCR1A,COM1A1);
	SETBIT(TCCR1A,COM1B1); 
	
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM12);
	CLRBIT(TCCR1B,WGM13);
	SETBIT(TCCR1B,CS10);
	
}
	
	void PWM1_OCR1A_DUTY(uint8_t duty)
	{
		OCR1A = duty * 10.23;
		OCR1B = duty * 10.23;
		
	}
	
	
	
	
