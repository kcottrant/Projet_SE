// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void aiguilles(uint8_t numero_cadran, uint8_t compteur_h,uint8_t compteur_min,uint8_t compteur_sec);
