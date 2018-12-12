// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define L_BARRE 15 //15cm

float measure_angular_speed();
void transmit4displayLED(int theta, int sec, int min, int hour);
void timer0_init();
