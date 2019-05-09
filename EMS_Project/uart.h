/*
 * IncFile1.h
 *
 * Created: 4/27/2018 4:50:07 PM
 *  Author: Ahmed Nasr
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "stdint_macro.h"

void UART_init();

void UART_send(uint8_t data);

uint8_t UART_rec();





#endif /* INCFILE1_H_ */