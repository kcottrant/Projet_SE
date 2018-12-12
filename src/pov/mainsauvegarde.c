// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//|(0 << SPIE);
 /* set global interrupt enable */
  /* enable global interuption*/
  //SPSR |= _BV(SPIF);
  // unsigned char p=0x80;
  // SREG |= p;
}

void SPI_MasterTransmit(uint8_t cData)
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
  UCSR0A=0;
  UCSR0B=0;
  UCSR0C =0;
  // UCSR0A = (1<<RXC0);
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE0);
  // enable interrupt USART sur RXCIE0
  /* Set frame format: 8data, 2stop bit */
  //  UCSR0C = (1<<USBS0)|(3<<UCSZ00); /* Set baud rate */
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

unsigned char USART_Receive( void )
{
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) );
  /* Get and return received data from buffer */
  return UDR0;
}

void allumeLed(uint16_t chiffre)
{
  uint8_t trame1= chiffre>>8;
  uint8_t trame2 = chiffre;
  PORTE |= _BV(PE4);
  PORTE &=~ _BV(PE5);
  
  SPI_MasterTransmit(trame1);
  SPI_MasterTransmit(trame2);
  PORTE |= _BV(PE5);
  // OFF pour LE
  //PORTE &=~ _BV(PE5);
  // OFF envoie au OE
  PORTE &=~ _BV(PE4);
  // ON envoie au OE A DECOMMENTER SI ON VEUT PLEINE PUISSANCE
  //PORTE |= _BV(PE4);

}

// interruption pour l'envoie de commandes USART 

ISR(USART0_RX_vect)
{
  unsigned char data;
  //Read the received data 
  data = UDR0;
  USART_Transmit(data);
}

void InitEffetHall(void)
{
  EIMSK &=~_BV(INT0);
  EICRA &=~ _BV(ISC00);
  EICRA |= _BV(ISC01);
  EIMSK |=_BV(INT0);
}

ISR(INT0_vect)
{
   USART_Transmit('a');
}


int main() {
  sei();
  // Lecture et écriture
  USART_Init(MYUBRR);
  //USART_Transmit('b');
  InitEffetHall();
  while(1){}

  
  /* 
  // Connexion SPI (communication avec les LED)
  SPI_MasterInit();

  volatile uint16_t i=1;

  while (i<=32768)
    {
      allumeLed(i);
      _delay_ms(400);
      if(i>=32768)
      {
	i=1;
	allumeLed(1);
	_delay_ms(400);
      }
      i=i*2;
    }
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
    _delay_ms(1000);
    }*/
}


