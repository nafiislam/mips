/*
 * atmega.c
 *
 * Created: 15-Feb-23 12:12:05 AM
 * Author : NafiIslam
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000 // Clock Frequency
#include <util/delay.h>

volatile unsigned short int control[16][2]={{0x8,0xd1}, {0x0,0x1}, {0x8,0x11}, {0x0,0x9}, {0x9,0x02}, {0x8,0x13}, {0x0,0x3}, {0x8,0x17}, {0xa,0x02}, {0x8,0x1b}, {0x8,0x1d}, {0x0,0x5}, {0xc,0x00}, {0x8,0x15}, {0x0,0x7}, {0x8,0x30}};
ISR(INT0_vect) {
	unsigned char opcode;
	opcode = (PIND & 0b01111000)>>3;
	PORTA = control[opcode][1] & 0b11111111;
	PORTC = (control[opcode][0] & 0b00001111)<<4;
}


int main(void)
{
    DDRA = 0xFF;//output
    DDRC = 0xFF;//output
    DDRD = 0x00;//input
    
    GICR |= (1<<INT0); // enable int0
    MCUCR |= (1<<ISC01)|(1<<ISC00); // 11 in interrupt0 sense control for sensing rising edge
	
    MCUCSR = (1<<JTD);
    MCUCSR = (1<<JTD);
    sei();
	

    while (1)
    {
    }
}

