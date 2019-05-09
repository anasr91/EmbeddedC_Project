/*
 * adc.h
 *
 * Created: 4/20/2018 7:14:55 PM
 *  Author: Ahmed Nasr
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "stdint_macro.h"

void ADC_init();

uint16_t ADC_read(uint8_t channel);





#endif /* ADC_H_ */