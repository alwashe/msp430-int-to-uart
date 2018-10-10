/*
 * pinaction.h
 *
 *  Created on: 18.11.2015
 *  Update: 19.11.2015
 *      Author: Amin Alwashe
 *
 *      pin# 2-15 18-19
 *
 *      pin# 2 = P1.0
 *      pin# 3 = P1.1
 *      pin# 4 = P1.2
 *      pin# 5 = P1.3
 *      pin# 6 = P1.4
 *      pin# 7 = P1.5
 *      pin# 8 = P2.0
 *      pin# 9 = P2.1
 *      pin# 10 = P2.2
 *      pin# 11 = P2.3
 *      pin# 12 = P2.4
 *      pin# 13 = P2.5
 *      pin# 14 = P1.6
 *      pin# 15 = P1.7
 *      pin# 18 = P2.7
 *      pin# 19 = P2.6
 *
  */

#include <msp430.h>
#include <stdint.h>



void digitalWrite(uint8_t pin, uint8_t state);
void pinMode(uint8_t pin, uint8_t mode);
uint8_t getPortpin(uint8_t pin);
uint8_t getPort(uint8_t pin);


void digitalWrite(uint8_t pin, uint8_t state) {
	//Port 1 & HIGH
	if (getPort(pin)==1&&state==1) {
		P1OUT |= (1 << getPortpin(pin));
	}
	//Port 2 & HIGH
	if (getPort(pin)==2&&state==1) {
		P2OUT |= (1 << getPortpin(pin));
	}
	//Port 1 & LOW
	if (getPort(pin)==1&&state==0) {
		P1OUT &= ~(1 << getPortpin(pin));
	}
	//Port 2 & LOW
	if (getPort(pin)==2&&state==0) {
		P2OUT &= ~(1 << getPortpin(pin));
	}
	//Port 1 & TOGGLE
	if (getPort(pin)==1&&state==3) {
		P1OUT ^= (1 << getPortpin(pin));
	}
	//Port 2 & TOGGLE
	if (getPort(pin)==2&&state==3) {
		P2OUT ^= (1 << getPortpin(pin));
	}
}

void pinMode(uint8_t pin, uint8_t mode) {
	//Port 1 & Output
	if (getPort(pin) == 1 && mode == 1) {
		P1DIR |= (1 << getPortpin(pin));
	}
	//Port 2 & Output
	if (getPort(pin) == 2 && mode == 1) {
		P1DIR |= (1 << getPortpin(pin));
	}
	//Port 1 & Input
	if (getPort(pin) == 1 && mode == 2) {
		P1DIR &= ~(1 << getPortpin(pin));
	}
	//Port 2 & Input
	if (getPort(pin) == 2 && mode == 2) {
		P2DIR &= ~(1 << getPortpin(pin));
	}
	//Port 1 & Input & PULL_UP
	if (getPort(pin) == 1 && mode == 3) {
		P1DIR &= ~(1 << getPortpin(pin));
		P1REN |= (1 << getPortpin(pin)); 						// Pull-Widerstand ein
		P1OUT |= (1 << getPortpin(pin)); 						// Pull up
	}
	//Port 2 & Input & PULL_UP
	if (getPort(pin) == 2 && mode == 3) {
		P2DIR &= ~(1 << getPortpin(pin));
		P2REN |= (1 << getPortpin(pin)); 						// Pull-Widerstand ein
		P2OUT |= (1 << getPortpin(pin)); 						// Pull up
	}
}

uint8_t getPortpin(uint8_t pin) {
	uint8_t portPin;

	switch (pin) {
	case 1:
		portPin = 30;
		break;
	case 2:
		portPin = 0;
		break;
	case 3:
		portPin = 1;
		break;
	case 4:
		portPin = 2;
		break;
	case 5:
		portPin = 3;
		break;
	case 6:
		portPin = 4;
		break;
	case 7:
		portPin = 5;
		break;
	case 8:
		portPin = 0;
		break;
	case 9:
		portPin = 1;
		break;
	case 10:
		portPin = 2;
		break;
	case 11:
		portPin = 3;
		break;
	case 12:
		portPin = 4;
		break;
	case 13:
		portPin = 5;
		break;
	case 14:
		portPin = 6;
		break;
	case 15:
		portPin = 7;
		break;
	case 16:
		portPin = 28;
		break;
	case 17:
		portPin = 29;
		break;
	case 18:
		portPin = 7;
		break;
	case 19:
		portPin = 6;
		break;
	case 20:
		portPin = 31;
		break;

	default:
		portPin = 30;
		break;
	}
	return portPin;

}

uint8_t getPort(uint8_t pin) {
	uint8_t port;

	switch (pin) {
	case 1:
		port = 0;
		break;
	case 2:
		port = 1;
		break;
	case 3:
		port = 1;
		break;
	case 4:
		port = 1;
		break;
	case 5:
		port = 1;
		break;
	case 6:
		port = 1;
		break;
	case 7:
		port = 1;
		break;
	case 8:
		port = 2;
		break;
	case 9:
		port = 2;
		break;
	case 10:
		port = 2;
		break;
	case 11:
		port = 2;
		break;
	case 12:
		port = 2;
		break;
	case 13:
		port = 2;
		break;
	case 14:
		port = 1;
		break;
	case 15:
		port = 1;
		break;
	case 16:
		port = 0;
		break;
	case 17:
		port = 0;
		break;
	case 18:
		port = 2;
		break;
	case 19:
		port = 2;
		break;
	case 20:
		port = 0;
		break;

	default:
		port = 0;
		break;
	}
	return port;
}
