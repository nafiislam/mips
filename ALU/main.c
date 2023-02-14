/*
 * GccApplication1.c
 *
 * Created: 2/13/2023 12:59:29 PM
 * Author : nahin
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000 // Clock Frequency
#include <util/delay.h>

ISR(INT0_vect) {
	unsigned char input1, input2, result, control, zeroFlag, output;
	input1 = PINB;
	input2 = PIND;
	control = PINA;
	input1 &= 0b00001111;
	input2 &= 0b01111000;
	input2 = input2 >> 3;
	control &= 0b00000111;
	
	result = 0b00000000;
	
	if ((control & 0) == 1)
	{
		result = input1 + input2;
	}
	else if((control & 1) == 1)
	{
		result = input2 - input2;
	}
	else if((control & 2) == 1)
	{
		result = input1 & input2;
	}
	else if((control & 3) == 1)
	{
		result = input1 | input2;
	}
	else if((control & 4) == 1)
	{
		result = input1 | input2;
		result = ~result;
	}
	else if((control & 5) == 1)
	{
		result = input1 << input2;
	}
	else if((control & 6) == 1)
	{
		result = input2 >> input1;
	}
	else
	{
		
	}
	
	if (result == 0)
	{
		zeroFlag = 1;
	}
	else
	{
		zeroFlag = 0;
	}
	
	result = result & 0b00001111;
	result = result << 4;
	//result = result & 0b11110000;
	zeroFlag = zeroFlag << 3;
	
	output = result | zeroFlag;
	PORTA = output;
	
	
}


int main(void)
{
    /* Replace with your application code */
	DDRA = 0b11111000;
	DDRB = 0b00000000;
	DDRD = 0b00000000;
	
	// set up interrupt
	GICR |= (1<<INT0); 
	MCUCR |= (1<<ISC01)|(1<<ISC00);
	sei();
	
    while (1) 
    {
		
    }
}

