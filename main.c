// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void JTAG_Init()
{
    /* Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0A = 1<<U2X0;
    /* Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit
    UCSR0C = (3<<UCSZ00);
    */

    // Enable JTAG
    MCUCSR= 1<<JTD;
    // RESET AVR_RESET
    //AVR_RESET |=_BV(PC6)
}

void JTAG_Transmit(unsigned char data )
{
    /* Wait for empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data
    UDR0 = data;
     */
}

void USART_Init( unsigned int ubrr )
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN)|(1<<TXEN);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) )
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

int main() {



/*  while(1){
    printf("%s\n", "hello");

  }*/

  // Paramètre en sortie
  //RXD |= _BV(PE0);
  // Définit la broche à "High"
  //TXD |= _BV(PE1);

  USART_Init(MYUBRR);

  char hello[128];
  int sizeHello = sprintf(hello, "Hello World!\n\r");
  char bye[128];
  int sizeBye = sprintf(bye, "Bye bye!\n\r");

  while(1)
  {
       //LED OFF
      //_delay_ms(500);              // 1s delay
      //PORTB &= ~_BV(PB5);      // LED off
      int i;
      for(i = 0; i < sizeBye; i++)
          USART_Transmit(bye[i]);

      // LED ON
      //_delay_ms(500);              // 1s delay
      //PORTB |= _BV(PB5);       // LED on

      for(i = 0; i < sizeHello; i++)
          USART_Transmit(hello[i]);
  }
}
