#include "spi.h"
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
}

void SPI_MasterTransmit(uint8_t cData)
{
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}

// allume les LED à partir d'un chiffre décimal
void allumeLed(uint16_t chiffre)
{
  uint8_t trame1= chiffre>>8;
  uint8_t trame2 = chiffre;
  PORTE |= _BV(PE4);
  PORTE &=~ _BV(PE5);
  
  SPI_MasterTransmit(trame1);
  SPI_MasterTransmit(trame2);
  PORTE |= _BV(PE5);
  PORTE &=~ _BV(PE4);
}
