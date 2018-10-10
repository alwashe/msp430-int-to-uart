#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>

void putchar(char c);
char getchar();
void puts(const char *s);
void putint(long intzahl);
void nLine();
void putfloat(float floatzahl);
long float2int(float zahl);


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

	nLine();
	nLine();
	puts("###########");
	nLine();
	puts("#  RESET  #");
	nLine();
	puts("###########");
	nLine();
	nLine();
	puts("serielle Schnittstelle initialisiert");
	nLine();
	nLine();
}

void putchar(char c) {
	while ((IFG2 & UCA0TXIFG) == 0)
		;
	UCA0TXBUF = c;
}

char getchar() {
	while ((IFG2 & UCA0RXIFG) == 0)
		;
	return UCA0RXBUF;
}

void puts(const char *s) {
	while (*s != '\0') {
		putchar(*s);
		s++;
	}
}

void putint(long intzahl) {
	char buffer[30];
	ltoa((long) intzahl, buffer);
	puts(buffer);
}

void putfloat(float floatzahl) {
	long intzahl;
	long stelle;

	intzahl = float2int(floatzahl);				// 1,23 => 123

	if (intzahl < 1000) {
		char buf[5] = "";

		int8_t i = 3;
		while (i >= 0) {						// i=3,2,1,0
			if (i == 1) {
				buf[i] = ',';
			} else {
				stelle = intzahl % 10;
				buf[i] = stelle + '0';
				intzahl = (intzahl / 10);
			}
			i--;
		}
		puts(buf);
	} else if (intzahl < 10000) {	//	10,00-99,99			Intzahl: 1000-9999
		char buf[6] = "";

		int8_t i = 4;
		while (i >= 0) {						// i=3,2,1,0
			if (i == 2) {
				buf[i] = ',';
			} else {
				stelle = intzahl % 10;
				buf[i] = stelle + '0';
				intzahl = (intzahl / 10);
			}
			i--;
		}

		puts(buf);
	} else if (intzahl < 100000) {//	100,00-999,99			Intzahl: 10000-99999
		char buf[7] = "";

		int8_t i = 5;
		while (i >= 0) {						// i=3,2,1,0
			if (i == 3) {
				buf[i] = ',';
			} else {
				stelle = intzahl % 10;
				buf[i] = stelle + '0';
				intzahl = (intzahl / 10);
			}
			i--;
		}
		puts(buf);
	}
}

void nLine() {
	puts("\r\n");
}

long float2int(float zahl) {
	return (long) (zahl*100.0);
}
