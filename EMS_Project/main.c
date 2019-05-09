/*
 * EMS_Project.c
 *
 * Created: 7/10/2018 6:02:27 PM
 * Author : Ahmed Nasr
 */ 

#include <avr/io.h>
#include "adc.h"
#include "stdint_macro.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "uart.h"
#include "pwm.h"


volatile  uint8_t i = 0; //----  interrupt counter.
volatile uint8_t ii = 0; //---- Mode counter.


int main(void)
{
	LCD_init(); // ---- LCD Initialization.
	UART_init(); // ---- UART Initialization.
	
	
	SETBIT(GICR,INT0);//---- INT0 Interrupt - rising edge
	SETBIT(MCUCR,ISC00);//---- //     //     //
	SETBIT(MCUCR,ISC01);//---- //     //     //
	sei();//---- //     //     //
	

	SETBIT(UCSRA,RXC);
	SETBIT(UCSRB,RXCIE);

    while (1) 
    {
		
		CLRBIT(DDRD,3);
		CLRBIT(DDRD,4);
		CLRBIT(DDRD,5);
		//---------------------------- MODE 1 --------------------------------------------------//
		
		 if(ii==1)
		 {
			 
			  LCD_command(0x01);
			  
			  ADC_init(); // ---- ADC Initialization.
			  PWM1_OCR1A_init(); // ---- PWM Initialization.
			  
			  LCD_command(0x85);//---- First line 6th bit
			  LCD_STRING("mode 1");
			  
			  LCD_command(0xC3);//---- Second line 3rd bit
			  LCD_STRING("Fire Alarm");
			  
			  
			 while(1)
			 {
				
				 if (ADC_read(0) < 100) 
				 {
					 PWM1_OCR1A_DUTY(10);
					 
				 }
				 else if ((ADC_read(0) >= 100) && (ADC_read(0) < 300))
				 {
					 PWM1_OCR1A_DUTY(30);
				 }
				 else if ((ADC_read(0) >= 300) && (ADC_read(0) < 600))
				 {
					 PWM1_OCR1A_DUTY(70);
				 }
				 else PWM1_OCR1A_DUTY(100);
				 
				 
				 if (ii != 1) break;
				 
				 
			 }
		 }
		 
		 //---------------------------------- MODE 2 --------------------------------------------//
		 else if(ii==2)
		 {
			 LCD_command(0x01);
			 
			 LCD_command(0x85);
			 LCD_STRING("mode 2");
			 
			 LCD_command(0xC2);
			 LCD_STRING("Light Sensor");
			 
			 SETBIT(DDRD,3); //-----Relay.
			 
			 while(1)
			 {
				 if (ADC_read(0) > 500)
				 {
					 SETBIT(PORTD,3); //----- enable relay
				 }
				 else CLRBIT(PORTD,3);
				 
				 if (ii != 2) break;
			 }
			 
			
		 }
		 
		 //-------------------------- MODE 3 ----------------------------------------------------------------//
		 
		 else if(ii==3)
		 {
			 i=0;//---- Resets Interrupt counter.
			
		//	uint8_t data, count =1 , i,j,op,k =0;// data=>key pressed, count=># of pressed keys,i&j=>for array loops,op=>operation,k=>flag for number 1 and 2
		//	 int num1[4],num2[4];// number 1 and number 2 arrays
		//	 uint16_t first, second, res;// full number 1 & 2
			 
			 
			 
			 
			 uint16_t num1tim10,num1tim1,num2tim10,num2tim1,num1,num2,minus;
			 
			 float res,all_digits;
			 
			 char operation;
			 
			 uint8_t count=0;
			 
			 
			 uint8_t data=0;
			 
			 
			 KEYPAD_init();//--- keypad initialization
			  LCD_command(0x01);//----- clear screen
			 
			 
			  
			  LCD_command(0x85);//------ start in the middle
			  LCD_STRING("mode 3");
			  
			  
			  LCD_command(0xC0);//------ start in the second line
			   
			   while(1)
			 {
				 /*
					data = KEYPAD_SCAN();
					
					if(data!=100)
					{
						
						
						while (((!READBIT(PINC,0))) || ((!READBIT(PINC,1))) || ((!READBIT(PINC,2))) || ((!READBIT(PINC,3))));//latch
						
						_delay_ms(200);
						
						LCD_data(data);
						
					//if (ii != 3) break;
					}
					
					if (data=='C')	//resets calculator, key => *			
					{
						LCD_command(0x01);
						LCD_command(0x85);
						LCD_STRING("mode 3");
						LCD_command(0xc0);
						count =1;
						k=0;
					}
					
					
					
					if (data != ('+' || '-' || '*' || '/')) //----- if pressed is not an operation
					{
						
							if( k=0)//---- flag for first number
							{
								num1[count-1] = data - 48; //-----put number in the array and then increment counter
								count ++;
								
							}
							if (k=1)//------ flag for second number
							{
								num2[count-1] = data - 48; //-----put number in the array and then increment counter
								count ++;
							
							}
					}
					
						
					
					
						if (data == ('+' || '-' || '*' || '/' ) )  //----- if operation is pressed
						{
							op = data - 48; //---- save operation
							
							
							for( i =count; i>0; i--) // loop numbers saved in array and save the number in one variable
							{
								if( i = 4) j=1000; // if fourth digit - thousands
								if( i = 3) j=100; // if third digit - hundreds
								if( i = 2) j=10; // if second digit -  tens
								if( i = 1) j=1; // if first digit - units
								
								first += num1[i-1]*j; //add the digit multiplied by its j
							}
							count =1;
							k=1;
							
						}
						
						
				
					
					
					while (data == '=')
					{
						
						
						for( i =count; i>0; i--)
						{
							if( i = 4) j=1000;
							if( i = 3) j=100;
							if( i = 2) j=10;
							if( i = 1) j=1;
							
							second += num2[i-1]*j;
						}
						
						k=0;
						count =1;
						LCD_char('=');
						LCD_SNUMBER(25);
						
						switch(op)
						{
							case'+':
							LCD_num(first + second);
							break;
							
							case'-':
							LCD_num(first - second);
							break;
							
							case'*':
							LCD_num(first * second);
							break;
							
							case'/': 
							LCD_SNUMBER(first / second);
							break;
							
						}
				
						
					}*/
				 
				 
				 
				 
				 
				 data= KEYPAD_SCAN(); // to scan the entered character from key pad
				 _delay_ms(10);// to avoid re bouncing
				 
				 //while (((READBIT(PINC,0))!=1) || ((READBIT(PINC,1))!=1) || ((READBIT(PINC,2))!=1) || ((READBIT(PINC,3))!=1));
				 while (((!READBIT(PINC,0))) || ((!READBIT(PINC,1))) || ((!READBIT(PINC,2))) || ((!READBIT(PINC,3)))); // latch
				 
				 _delay_ms(100);// by try and error to avoid hard ware error on the kit
				 
				 
				 if (data!=100) // 100 if no data is entered the key pad function returns 100
				 {
					// LCD_data(data);
					 
					 if ( (data!=('o')) )
					 // o is on button so the count for the digit place will be 0 with o
					 //and will need to be incremented with any other push button
					 {
						 count++;  // count of the digit place
					 }
					 LCD_char(data); // writing the character from data key pad to LCD
					 _delay_ms(200); // to avoid repeating writing (try and error)
					 
					 if (data=='o') // on push botton on key pad
					 {
						 LCD_command(0x01);
						  LCD_command(0x85);//------ start in the middle
						  LCD_STRING("mode 3");
						  
						  
						  LCD_command(0xC0);//------ start in the second line
						 count=0; //because the digits places will start from zero again
					 }
					 
					 else if (count==1) // if the first digit is written
					 {
						 num1tim10=(data-48); // to change from ascii to the number
						 
					 }
					 
					 else if (count==2) // if the second digit is written
					 {
						 num1tim1=(data-48);  // to change from ascii to the number
						 
					 }
					 else if (count==3) // if the third digit is written
					 {
						 switch (data) // the operation is written in 3rd place
						 {
							 case '+':
							 operation='+';
							 break;
							 
							 case '-':
							 operation='-';
							 break;
							 
							 
							 case '*':
							 operation='*';
							 break;
							 
							 case '/':
							 operation='/';
							 break;
							 
							 case '=':
							 operation='=';
							 break;
						 }
					 }
					 else if (count==4)// first digit of second number (tens)
					 {
						 num2tim10=(data-48);//from ascii to number
					 }
					 else if (count==5)// second digit of second number (units)
					 {
						 num2tim1=(data-48);//from ascii to number
					 }
					 
					 else if (count==6) // it must be = or error will appear
					 {
						 if (data=='=')
						 {
							 if (operation=='+')
							 {
								 //case '+':
								 LCD_command(0xc0); // write the result in the second line on LCD
								 LCD_num(((num1tim10*10)+num1tim1)+((num2tim10*10)+num2tim1)); // add result display
							 }
							 
							 // 	case '-':
							 else if (operation=='-')
							 {
								 LCD_command(0xc0); // write the result in the second line on LCD
								 num1=((num1tim10*10)+num1tim1); // first number value
								 num2=((num2tim10*10)+num2tim1); // second number value
								 if (num1>=num2)
								 {
									 minus=(num1)-(num2);
									 LCD_num(minus); //positive result if the first number higher than he second
								 }
								 else
								 {
									 minus=(num2)-(num1);
									 LCD_char('-'); // if the second number is larger than the first
									 LCD_num(minus);
								 }
								 
							 }
							 else if (operation=='*')
							 {
								 // case '*':
								 LCD_command(0xc0);
								 LCD_num((((num1tim10*10)+num1tim1))*(((num2tim10*10)+num2tim1)));
							 }
							 else if (operation=='/')
							 {
								 
								 
								 //case '/':
								 
								 num1=(num1tim10*10)+num1tim1;
								 num2=(num2tim10*10)+num2tim1;
								 res=((float)num1)/((float)num2);// casting because the result will be float
								 all_digits=res*100; // multiplied by 100 to be Integer number not fraction
								 LCD_command(0xc0); // write on the second line
								 LCD_SNUMBER((uint16_t)all_digits); //to write the first the numbers before and after the fraction dot
								 
							 }
							 else // if the operation 3rd digit isn't arithmetic
							 {
								 LCD_command(0xc0);
								 LCD_STRING("error");
							 }

							 
						 } // end of if (data=='=')
						 
						 else // if the 6th not =
						 {
							 LCD_command(0xc0);
							 LCD_STRING("error");
							 
						 }
					 }// end of else if (count==6)
					 
					 
				 }// end of data != 100

					
						 
							
		if (ii != 3) break;
					
					
					}
					if (ii != 3) break;
			 }
		 }
}
			 





ISR(INT0_vect)
{
	_delay_ms(100);
	i++;
	UART_send(i);
}


ISR (USART_RXC_vect)
{
	
	ii=UART_rec();
}
