// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

//#define FOSC 1843200// Clock Speed
#define FOSC 13000000// Clock Speed
//1843200
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
  DDRB = (1<<DDB2)|(1<<DDB1);
  //enable OE
  DDRE |= _BV(PE4);
  //enable pour LE
  DDRE |= _BV(PE5);

  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)))
  ;
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

  // Paramètre en sortie
  //RXD |= _BV(PD0);
  // Définit la broche à "High"
  //TXD |= _BV(PD1);
  char byte1 = 0xaa; //00110000;
  char byte2 = 0xaa; //00100000;

  USART_Init(MYUBRR);
  USART_Transmit('b');
  SPI_MasterInit();

  // OFF pour LE
//  PORTE &=~ _BV(PE5); --> merde qd pas en commentaire
    // ON envoie au OE
  PORTE |= _BV(PE4);

while(1){
//_delay_ms(5);
  //on OE
  // DDRE |= _BV(PE4);
    SPI_MasterTransmit(byte1);
    SPI_MasterTransmit(byte2);
//  _delay_ms(100);
    //on OE
  //  DDRE &=~ _BV(PE4);
  //   ON pour LE
    PORTE |= _BV(PE5);
  // OFF pour LE
    PORTE &=~ _BV(PE5);
    // OFF envoie au OE
    PORTE &=~ _BV(PE4);
    // ON envoie au OE
    PORTE |= _BV(PE4);
}
  /*char hello[128];
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
  }*/
}
