#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>

void nLine();
void putfloat(float floatzahl);
void putchar(char c);
char getchar();
void puts(const char *s);
void putint(int intzahl);

void initBCM() {
	if (CALBC1_1MHZ != 0xFF) {
		DCOCTL = 0x00;						// Kalibrierte Werte für Takt 1 MHz
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
	}
}

void initUART() {
	P1SEL |= (1 << 2) | (1 << 1); 			// P1.1 und P1.2 dem USCI zuordnen
	P1SEL2 |= (1 << 2) | (1 << 1);
	UCA0CTL1 |= UCSWRST;					// RESET-Zustand zur Konfiguration
	UCA0CTL0 = 0;							// 8N1, LSB zuerst, UART, asynchron
	UCA0CTL1 = UCSSEL_2 | UCSWRST;			// SMCLK

	UCA0BR0 = 104;							// 9600 Baud bei Takt 1 MHz
	UCA0BR1 = 0;

	UCA0MCTL = UCBRS_1;						// UCBRFx=0, UCBRSx= 1, UCOS16=0
	UCA0CTL1 &= ~UCSWRST;					// RESET-Zustand beenden
}

void putchar(char c) {
	while ((IFG2 & UCA0TXIFG) == 0);
	UCA0TXBUF = c;
}

char getchar() {
	while ((IFG2 & UCA0RXIFG) == 0);
	return UCA0RXBUF;
}

void puts(const char *s) {
	while (*s != '\0') {
		putchar(*s);
		s++;
	}
}

void putint(int intzahl) {
	char buffer[10];
	ltoa((long) intzahl, buffer);
	puts(buffer);
}

void nLine() {
	puts("\r\n");
}
