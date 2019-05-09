/*
 * key_pad.c
 *
 * Created: 4/25/2018 2:53:24 PM
 *  Author: Ahmed Nasr
 */ 
# include "KEYPAD.h"
# include "stdint_macro.h"

//static const uint8_t keypad_matrix[]={'7','4','1','o','8','5','2','0','9','6','3','=','/','*','-','+'};//PROTOS KEY PAD
static const uint8_t keypad_matrix[]={'/','=','0','o','-','9','8','7','+','6','5','4','*','3','2','1'};//HARD ware KEY PAD

void KEYPAD_init()
{
	DDRC =0b11110000; //1111 input pins in port c
	PINC =0b00001111;//1111 makes the pins pullup
	
}

uint8_t KEYPAD_SCAN()
{
	PORTC=0b11101111;//use the 0 to check the first raw
	 //test
	 
	
	if (!READBIT(PINC,0)) {return keypad_matrix[0];}	//not ok the latch is not working on hard ware it works on protos only
	if (!READBIT(PINC,1)) {return keypad_matrix[1];}
	if (!READBIT(PINC,2)) {return keypad_matrix[2];}
	if (!READBIT(PINC,3)) {return keypad_matrix[3];}
		
	
	
	
	
		PORTC=0b11011111;//use the 0 to check the first raw
		if (!READBIT(PINC,0)) {return keypad_matrix[4];} //not ok the latch is not working on hard ware it works on protos only
		if (!READBIT(PINC,1)) {return keypad_matrix[5];}
		if (!READBIT(PINC,2)) {return keypad_matrix[6];}
		if (!READBIT(PINC,3)) {return keypad_matrix[7];}
		
			PORTC=0b10111111;//use the 0 to check the first raw
			if (!READBIT(PINC,0)) {return keypad_matrix[8];}  //not ok the latch is not working on hard ware it works on protos only
			if (!READBIT(PINC,1)) {return keypad_matrix[9];}
			if (!READBIT(PINC,2)) {return keypad_matrix[10];}
			if (!READBIT(PINC,3)) {return keypad_matrix[11];}
			
				PORTC=0b01111111;//use the 0 to check the first raw
				if (!READBIT(PINC,0)) {return keypad_matrix[12];} //not ok	the latch is no working on hard ware it works on protos only
				if (!READBIT(PINC,1)) {return keypad_matrix[13];}
				if (!READBIT(PINC,2)) {return keypad_matrix[14];}
				if (!READBIT(PINC,3)) {return keypad_matrix[15];}
					
				
				
				return 100;
}