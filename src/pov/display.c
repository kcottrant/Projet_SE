#include "display.h"

// timer 16 bit
void InitTimer1(uint8_t compteur_timer)
{
  // set prescaler 64
  TCCR1B |=_BV(CS11);
  TCCR1B |=_BV(CS10);
  // set offset 40625
  OCR1AH = 0x9E;
  OCR1AL = 0xB1;
  // set CTC mode
  TCCR1B |= _BV(WGM12);
  // enable overflow interrupt
  // enable l'interruption quand => offset
  TIMSK = (1 << OCIE1A);
  // compteur
  compteur_timer = 0;
}


// timer 16 bit
void InitTimer3(uint16_t vitesse)
{
  // set prescaler 64
  TCCR3B |=_BV(CS31);
  TCCR3B |=_BV(CS30);
  // set offset 40625
  vitesse = vitesse/60;
  OCR3AH = (vitesse>>8);
  OCR3AL = vitesse;
  // set CTC mode
  TCCR3B |= _BV(WGM32);
  // enable overflow interrupt
  // enable l'interruption quand => offset
  ETIMSK = (1 << OCIE3A);
}
