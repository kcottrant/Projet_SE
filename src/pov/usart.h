#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define FOSC 13000000// Clock Speed
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_puts(unsigned char *data);
