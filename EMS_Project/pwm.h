/*
 * pwm.h
 *
 * Created: 4/20/2018 7:13:58 AM
 *  Author: Ahmed Nasr
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "stdint_macro.h"

void PWM1_OCR1A_init();
void PWM1_OCR1A_DUTY(uint8_t duty);




#endif /* PWM_H_ */