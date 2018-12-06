// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 13000000// Clock Speed
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
  // enable port SS
  DDRB |= _BV(PB0);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}

void USART_Init( unsigned int ubrr )
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  //UCSR0C = (1<<USBS0)|(3<<UCSZ0);
  /* Set frame format: 8data, 1stop bit */
  UCSR0C =  (1<<UCSZ00)|(1<<UCSZ01);
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) )
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}



unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}


int main() {
  char byte1 = 0xaa; //00110000;
  char byte2 = 0xaa; //00100000;
  // Lecture et écriture
  USART_Init(MYUBRR);
//  USART_Transmit('b');

/*
  // Connexion SPI (communication avec les LED)
  SPI_MasterInit();

  // OFF pour LE
  PORTE &=~ _BV(PE5);
  // ON envoie au OE
  PORTE |= _BV(PE4);
  SPI_MasterTransmit(byte1);
  SPI_MasterTransmit(byte2);

  PORTE |= _BV(PE5);
  // OFF pour LE
  PORTE &=~ _BV(PE5);
    // OFF envoie au OE
  PORTE &=~ _BV(PE4);
      // ON envoie au OE A DECOMMENTER SI ON VEUT PLEINE PUISSANCE
  PORTE |= _BV(PE4);
  */

  // Effet Hall

//while(1)
  //{
  // enable PDO : entrée
  DDRD &=~(1<<PD0);//_BV(PD0);

    //PORTD |= _BV(PD0);
  //  unsigned char data = PORTD;

  //USART_Transmit('a');
   while(1==1)
    {
      unsigned char p = PORTD;
      char* pouet = atoi(p);
      int i = 0;
      while(pouet[i] != '\0')
        USART_Transmit(pouet[i]);
      //USART_Transmit('\n');
      //USART_Transmit('\r');
      _delay_ms(100);
    }

    /*
    //while(1){
      unsigned char p = 0x01;
      p &= PORTD;

      //USART_Transmit(data);
      if(p == 0x01){
        USART_Transmit('c');
      }
      if(p == 0x0){
        USART_Transmit('b');
      }
      //USART_Transmit(p);
      //_delay_ms(100);
    //}*/


  //}
}
