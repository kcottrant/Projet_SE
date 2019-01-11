#include "usart.h"
void USART_Init( unsigned int ubrr )
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0A=0;
  UCSR0B=0;
  UCSR0C =0;
  /* Enable receiver and transmitter */
  // enable interrupt USART sur RXCIE0
  UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE0);

  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void USART_Transmit( unsigned char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) )
    ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
  // attendre que la transmission soit finie
   while ( !( UCSR0A & (1<<TXC0)) )
   ;

}

// Permet d'envoyer plusieurs char à la fois
void USART_puts(unsigned char *data)
{
    int k = 0;

    while (data[k] != '\0') {
        USART_Transmit(data[k]);
        k++;
    }
}

unsigned char USART_Receive( void )
{
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) );
  /* Get and return received data from buffer */
  return UDR0;
}
