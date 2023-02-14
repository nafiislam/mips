/*
 * MemoryATMega.c
 *
 * Created: 2/13/2023 7:04:25 PM
 * Author : Naim
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000
#include <util/delay.h>

volatile int size = 16;
volatile unsigned char memory[256];

ISR(INT0_vect) {
	unsigned char memAddress, memWriteData, memWriteControl, memReadControl;
	memAddress = PINB;
	memWriteData = PIND;
	memAddress = memAddress & 0b00001111;
	memWriteControl = memWriteData & 0b00000001;
	memReadControl = memWriteData & 0b00000010;
	memWriteData = memWriteData & 0b01111000;
	memWriteData = memWriteData>>3;
	if (memWriteControl) {
		memory[memAddress] = memWriteData;
	}
	if (memReadControl) {
		PORTA = memory[memAddress];
	}
}

int main(void)
{
	DDRB = 0b00000000; // B as memory address (input)
	DDRD = 0b00000000; // D as memory write data (input)
	DDRA = 0b11111111; // A as memory read data (output)
    // initialize full memory to 0
	for (int i=0;i<size;i++) {
		memory[i] = 0;
	}
	// set up interrupt
	GICR |= (1<<INT0); // enable int0
	MCUCR |= (1<<ISC01)|(1<<ISC00); // 11 in interrupt0 sense control for sensing rising edge
	sei();	// enable global interrupt
	// continue to listen for interrupt
    while (1) 
    {
    }
}

