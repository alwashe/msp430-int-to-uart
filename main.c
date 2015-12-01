#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>

#include "uart_alw.h"
#include "pinaction.h"

uint8_t int2asci(uint8_t zahl);

uint8_t tempdavor = 0;
uint8_t temp = 0;									// Temperatur in °C/10

#define SW BIT3		//für Bit-Maske
#define SW1 5		//pin# =(pin und port)

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;					// Stopwatchdogtimer

	initBCM();									// Initialisierung UART
	initUART();									// Initialisierung UART

	pinMode(SW1, INPUT_PULLUP);
	P1IES &= ~SW; 						// Interrupt bei fallender Flanke
	P1IE |= SW; 						// Interrupt ein

	_bis_SR_register(GIE);				// Interrupts global ein

	nLine();							//puts("\r\n");  neue Zeile
	nLine();
	nLine();
	puts("###########");
	nLine();
	puts("#  RESET  #");
	nLine();
	puts("###########");
	nLine();

	while (1) {
		if (!(tempdavor == temp)) {
			char buf[5];
			buf[4] = '\0';
			int8_t i = 3;

			while (i >= 0) {
				buf[i] = int2asci(i);					// 1=>48	2=>49 etc
				i--;
			}
			puts(buf);
			nLine();

			tempdavor = temp;

		}
	}
}

uint8_t int2asci(uint8_t zahl) {
	uint8_t asci;
	switch (zahl) {
	case 0:	asci = 48;	break;
	case 1:	asci = 49;	break;
	case 2:	asci = 50;	break;
	case 3:	asci = 51;	break;
	case 4:	asci = 52;	break;
	case 5:	asci = 53;	break;
	case 6:	asci = 54;	break;
	case 7:	asci = 55;	break;
	case 8:	asci = 56;	break;
	case 9:	asci = 57;	break;
	default:asci = 65;	break;
	}
	return asci;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {

	temp++;
	if (temp >= 100) {
		temp = 0;
	}
	P1IFG &= ~SW; 						// Interrupt-Flaglöschen
}
