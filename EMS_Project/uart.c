/*
 * CFile1.c
 *
 * Created: 4/27/2018 4:49:53 PM
 *  Author: Ahmed Nasr
 */ 

#include "uart.h"
#include "stdint_macro.h"

void UART_init()
{
	
//	CLRBIT(UCSRC,6); // asych
	SETBIT(UCSRB,4); // Rx
	SETBIT(UCSRB,3);  // Tx
	//SETBIT(UCSRB,2);// ucsz2 FOR 8BIT
	//CLRBIT(UCSRC,4);//parity
	//CLRBIT(UCSRC,5); //parity
	SETBIT(UCSRC,1); //ucsz0
	SETBIT(UCSRC,2); //ucsz1
	UBRRL = 51;
	
}

void UART_send(uint8_t data)
{
	while (READBIT(UCSRA,5) ==0)
	{
	}
		UDR = data;
}

uint8_t UART_rec()
{
	while (READBIT(UCSRA,7) ==0)
	{
	}
		return UDR;
}
