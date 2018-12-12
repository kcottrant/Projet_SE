// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
//#include <util/delay.h>

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
  /* Enable SPI, Master, set clock rate fck/16, enable interuption*/
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
  //SPSR |= (1<<SPI2X);
  /* enable global interuption*/
  //unsigned char p=0x80;
  //SREG |= p;
  //__enable_interrupt(); /* set global interrupt enable */
  //sei();
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

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}

/*void allumeLed(char chiffre1, char chiffre2)
{
  SPI_MasterTransmit(chiffre1);
  SPI_MasterTransmit(chiffre2);

  PORTE |= _BV(PE5);
  // OFF pour LE
  PORTE &=~ _BV(PE5);
    // OFF envoie au OE
  PORTE &=~ _BV(PE4);
  // ON envoie au OE A DECOMMENTER SI ON VEUT PLEINE PUISSANCE
  //_delay_ms(1000);
  PORTE |= _BV(PE4);

}*/

int main() {


//  char byte1 = 0xaa; //00110000;
//  char byte2 = 0xaa; //00100000;
  char zero =0x00;
  char un = 0x01;
  char deux = 0x02;
  // Lecture et écriture
  //USART_Init(MYUBRR);
  //USART_Transmit(USART_Receive());
  // Connexion SPI (communication avec les LED)
  SPI_MasterInit();
  // OFF pour LE
  /*PORTE &=~ _BV(PE5);
  // ON envoie au OE
  PORTE |= _BV(PE4);
  while(1){
    SPI_MasterTransmit(zero);
    SPI_MasterTransmit(un);

    PORTE |= _BV(PE5);
    // OFF pour LE
    PORTE &=~ _BV(PE5);
      // OFF envoie au OE
    PORTE &=~ _BV(PE4);
    // ON envoie au OE A DECOMMENTER SI ON VEUT PLEINE PUISSANCE
    //_delay_ms(1000);
    PORTE |= _BV(PE4);
  }*/


  // OFF pour LE
  PORTE &=~ _BV(PE5);
  // ON envoie au OE
  PORTE |= _BV(PE4);
  while(1){
    SPI_MasterTransmit(deux);
    SPI_MasterTransmit(deux);

    PORTE |= _BV(PE5);
    // OFF pour LE
    PORTE &=~ _BV(PE5);
      // OFF envoie au OE
    PORTE &=~ _BV(PE4);
    // ON envoie au OE A DECOMMENTER SI ON VEUT PLEINE PUISSANCE
    //_delay_ms(1000);
    PORTE |= _BV(PE4);
  }


/*
    // Effet Hall
      while(1){
        unsigned char p = 0x01;
        p &= PIND;
        if(p == 0x0){
          USART_Transmit('g');
        }
        if(p == 0x01){
          USART_Transmit('c');
        }
        _delay_ms(10000000000000);
      }
*/
}
