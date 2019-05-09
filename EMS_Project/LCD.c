/*
 * LCD.c
 *
 * Created: 4/21/2018 5:05:10 PM
 *  Author: Ahmed Nasr
 */ 
#include "LCD.h"


#include "stdint_macro.h"

void LCD_init()
{
	LCD_INIT_DIR();
	LCD_RW(1);
	LCD_command(0x2);
	LCD_command(0x28);
	LCD_command(0x01);
	LCD_command(0x0c);
	LCD_command(0x06);
	LCD_command(0x80);
	_delay_ms(20);
	
	
}


void LCD_data(uint8_t data)
{
	LCD_RW(0);
	LCD_RS(1);
	
	
	for(int i=0;i<=3;i++)
	{
		if(READBIT(data,4+i) == 0)
		{
			CLRBIT(PORTA,4+i);
		}
		else
		{
			SETBIT(PORTA,4+i);
		}
	}
	
	LCD_E(1);
	_delay_ms(1);
	LCD_E(0);
	_delay_ms(1);
	
	for(int i=0;i<=3;i++)
	{
		if(READBIT(data,i) == 0)
		{
			CLRBIT(PORTA,4+i);
		}
		else
		{
			SETBIT(PORTA,4+i);
		}
}
	
	LCD_E(1);
	_delay_ms(1);
	LCD_E(0);
	_delay_ms(1);
	
	}

void LCD_command(uint8_t cmd)
{
	LCD_RW(0);
	LCD_RS(0);
	
	
	for(int i=0;i<=3;i++)
	{
		if(READBIT(cmd,4+i) == 0)
		{
			CLRBIT(PORTA,4+i);
		}
		else
		{
			SETBIT(PORTA,4+i);
		}
	}
	
	LCD_E(1);
	_delay_ms(1);
	LCD_E(0);
	_delay_ms(1);
	
	for(int i=0;i<=3;i++)
	{
		if(READBIT(cmd,i) == 0)
		{
			CLRBIT(PORTA,4+i);
		}
		else
		{
			SETBIT(PORTA,4+i);
		}
	}
	
	LCD_E(1);
	_delay_ms(1);
	LCD_E(0);
	_delay_ms(1);
	
}

void LCD_STRING(uint8_t *text)
{
	int i=0;
	while(text[i] != '\0')
	{
		LCD_data(text[i]);
		i++;
	}
}


void LCD_char(uint8_t data)
{
	LCD_RS(1);
	LCD_D7(READBIT(data,7));
	LCD_D6(READBIT(data,6));
	LCD_D5(READBIT(data,5));
	LCD_D4(READBIT(data,4));
	LCD_E(1);
	
	_delay_ms(1);
	
	LCD_E(0);
	
	_delay_ms(1);
	
	LCD_D4(READBIT(data,0));
	LCD_D5(READBIT(data,1));
	LCD_D6(READBIT(data,2));
	LCD_D7(READBIT(data,3));
	LCD_E(1);
	
	_delay_ms(1);
	
	LCD_E(0);
	
	_delay_ms(1);
	
}


void LCD_num(uint16_t num)

{
	uint16_t first, second, third, rem, rem1, fourth;
	
	if (num < 10)
	{
		LCD_char(num+48);
	}
	
	else if (num < 100)
	{
		first = num / 10;
		second = num % 10;
		LCD_char(first +48);
		LCD_char(second +48);
	}
	else if (num < 1000)
	{
		first = num/100;
		rem = num%100;
		second = rem/10;
		third = rem%10;
		LCD_char(first +48);
		LCD_char(second +48);
		LCD_char(third +48);
	}
	else if (num<10000)
	{
		first =num/1000;
		rem =num%1000;
		second =rem/100;
		rem1=rem%100;
		third =rem1/10;
		fourth=rem1%10;
		
		LCD_char(first+48);
		LCD_char(second+48);
		LCD_char(third+48);
		LCD_char(fourth+48);
	}
}



void LCD_SNUMBER(uint16_t num)
{
	uint16_t first,second,rem,third,rem1,fourth;
	
	if (num<10)
	{
		LCD_char(num+48);
	}
	
	else if (num<100)
	{
		first=num/10;
		second=num%10;
		LCD_char(first+48);
		LCD_char(second+48);
	}
	
	else if (num<1000)
	{
		first=num/100;
		rem=num%100;
		second=rem/10;
		third=rem%10;
		LCD_char(first+48);
		LCD_char(second+48);
		LCD_char(third+48);
	}
	
	else if (num<10000)
	{
		first=num/1000;
		rem=num%1000;
		second=rem/100;
		rem1=rem%100;
		third=rem1/10;
		fourth=rem1%10;
		
		LCD_char(first+48);
		LCD_char(second+48);
		LCD_char(third+48);
		LCD_char(fourth+48);
	}
}

