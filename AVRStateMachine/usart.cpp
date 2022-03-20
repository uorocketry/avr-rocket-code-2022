#include "stdafx.h"
#include "usart.h"
#include <string.h>

#define USART_BAUD_RATE(BAUD_RATE)     ((float)(64 * 4000000 / (16 * (float)BAUD_RATE)) + 0.5)

Usart::Usart(int id = 0) {
	if (id > 2 || id < 0 ) { 
		id = 0;
	}
	switch (id) 
	{
	case 0: 
		this->id = 0;
		PORTA.DIRSET = PIN0_bm;
		PORTA.DIRSET = PIN1_bm;
		USART0.BAUD = (uint16_t)(USART_BAUD_RATE(9600));
		USART0.CTRLC = USART_CHSIZE0_bm
					| USART_CHSIZE1_bm;
		USART0.CTRLB |= USART_TXEN_bm;
		break;
	case 1: 
		this->id = 1;
		PORTC.DIRSET = PIN0_bm;
		PORTC.DIRSET = PIN1_bm;
		USART1.BAUD = (uint16_t)(USART_BAUD_RATE(9600));
		USART1.CTRLC = USART_CHSIZE0_bm
					| USART_CHSIZE1_bm;
		USART1.CTRLB |= USART_TXEN_bm;
		break;
	case 2: 
		this->id = 2;
		PORTF.DIRSET = PIN4_bm;
		PORTF.DIRSET = PIN5_bm;
		USART2.BAUD = (uint16_t)(USART_BAUD_RATE(9600));
		USART2.CTRLC = USART_CHSIZE0_bm
					| USART_CHSIZE1_bm;
		USART2.CTRLB |= USART_TXEN_bm;
		break;
	}
}

void Usart::sendChar(char c)
{
	switch (this->id) {
		case 0: 
			while(!(USART0.STATUS & USART_DREIF_bm)) {
				;
			}
			USART0.TXDATAL = c;
			break;
		case 1:
			while(!(USART1.STATUS & USART_DREIF_bm)) {
				;
			}
			USART1.TXDATAL = c;
			break;
		case 2:
			while(!(USART2.STATUS & USART_DREIF_bm)) {
				;
			}
			USART2.TXDATAL = c;
			break;		 
	}
}

void Usart::sendString(char *str) {
	for (size_t i = 0; i < strlen(str); i++) {
		this->sendChar(str[i]);
	}
	this->sendChar('\n');
}

void Usart::readChar() {
	int id = this->id;
}

int Usart::getID() {
	return this->id;
}