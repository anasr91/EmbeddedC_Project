/*
 * LCD.h
 *
 * Created: 4/21/2018 5:05:28 PM
 *  Author: Ahmed Nasr
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "stdint_macro.h"

#define LCD_INIT_DIR() DDRA |= 0b11110000 ; DDRB |=0b1110;
#define LCD_RS(x) (x==0)? CLRBIT(PORTB,1): SETBIT(PORTB,1)
#define LCD_RW(x) (x==0)? CLRBIT(PORTB,2):  SETBIT(PORTB,2)
#define LCD_E(x) (x==0)? CLRBIT(PORTB,3):  SETBIT(PORTB,3)
#define LCD_D4(x) (x==0)? CLRBIT(PORTA,4):  SETBIT(PORTA,4)
#define LCD_D5(x) (x==0)? CLRBIT(PORTA,5):  SETBIT(PORTA,5)
#define LCD_D6(x) (x==0)? CLRBIT(PORTA,6):  SETBIT(PORTA,6)
#define LCD_D7(x) if(x==0) CLRBIT(PORTA,7);  SETBIT(PORTA,7)

void LCD_init();
void LCD_data(uint8_t data);
void LCD_command(uint8_t cmd);
void LCD_STRING(uint8_t *text);
void LCD_SNUMBER(uint16_t num);
void LCD_char(uint8_t data);
void LCD_num(uint16_t number);


#endif /* LCD_H_ */