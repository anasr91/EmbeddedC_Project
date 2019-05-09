/*
 * key_pad.h
 *
 * Created: 4/25/2018 2:53:40 PM
 *  Author: Ahmed Nasr
 */ 


#ifndef KEY_PAD_H_
#define KEY_PAD_H_
#include <avr/io.h>

//key pad initialization
void KEYPAD_init();
// key pad scan (get new click
uint8_t KEYPAD_SCAN();





#endif /* KEY_PAD_H_ */