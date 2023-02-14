/*
 * 4_Bit_Processor.cpp
 *
 * Created: 2/12/2023 3:30:05 AM
 * Author : Asus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000 // Clock Frequency
#include <util/delay.h>


volatile unsigned char ins[256][2] = {
	{ 0xab, 0xcd},
	{ 0x12, 0x34},
	};

unsigned char reverseBits(unsigned char n)
{
	unsigned char rev = 0;
	
	// traversing bits of 'n' from the right
	while (n > 0) {
		// bitwise left shift
		// 'rev' by 1
		rev <<= 1;
		
		// if current bit is '1'
		if ((n & 1) == 1)
		rev ^= 1;
		
		// bitwise right shift
		// 'n' by 1
		n >>= 1;
	}
	
	// required number
	return rev;
}

void show_output(unsigned char addr){
	unsigned char a;
	a = ins[addr][0];
//	a = ((a & 0xf0) >> 4) | ((a & 0x0f) << 4);
	
	
	PORTA = reverseBits(a);//changed
	PORTC = ins[addr][1];
}

ISR(INT0_vect){
	//PORTB = ~PORTB;
	unsigned char c;
	unsigned char d;
	
	c = PORTB;
	c = c & 0x0f;
	c = reverseBits(c);
	
	d = PORTD;
	d = d & 0b01111000;
	d <<= 1;
	d = reverseBits(d);
	
	c = c | d;
	show_output(c);
	
}

int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF;
	DDRB = 0x0F;
	DDRC = 0xFF;
	DDRD = 0b10000111;
	
	GICR |= (1<<INT0); // enable int0
	MCUCR |= (1<<ISC01)|(1<<ISC00); // 11 in interrupt0 sense control for sensing rising edge
	
	MCUCSR = (1<<JTD);  
	MCUCSR = (1<<JTD); 
	sei();//STEP5
	
	//ins[0][1]
	show_output(0);
	
	
	
    while (1) 
    {
    }
	
	
	
	
}

