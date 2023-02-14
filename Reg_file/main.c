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

volatile unsigned char regi[8];
ISR(INT0_vect) {
	unsigned char regWrite, reg1, reg2,dst, data;
	regWrite = PIND & 0b00000001;
	reg1 = PINB & 0b00001111;
	reg2 = (PINB & 0b11110000)>>4;
	dst = (PIND & 0b01111000)>>3;
	data = PINC & 0b00001111;
	if(regWrite==0){ // only read
		PORTA = regi[reg1] & 0b00001111;
		PORTA |= (regi[reg2]<<4) & 0b11110000;
	}
	else if(regWrite==1){
		regi[dst] = data; // only write
	}
}


int main(void)
{
    DDRA = 0xFF;//output
    DDRB = 0x00;//input
    DDRC = 0x00;//input
    DDRD = 0x00;//input
    
    GICR |= (1<<INT0); // enable int0
    MCUCR |= (1<<ISC01)|(1<<ISC00); // 11 in interrupt0 sense control for sensing rising edge
	
    MCUCSR = (1<<JTD);
    MCUCSR = (1<<JTD);
    sei();
	int i;
	for(i=0;i<6;i++){
		regi[i]=0;
	}
	regi[6]=0xf;

    while (1)
    {
    }
}

