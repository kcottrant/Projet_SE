// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define L_BARRE 15 //15cm

void InitTimer1(uint8_t compteur_timer);
void InitTimer3(uint16_t vitesse);
