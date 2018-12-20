#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void chiffreun(uint8_t numero_cadran);
uint8_t calculLedAllume(uint16_t taba[16],uint16_t tabb[16], uint16_t posLedx, uint16_t posLedy);
uint16_t convertToDecimal(uint8_t tabled[16]);
void misezero(uint16_t *tab[16]);
uint16_t calculCoeffDirect(uint16_t x1,uint8_t x2,uint16_t y1,uint16_t y2);
uint16_t calculOrdonOrigin(uint16_t x,uint8_t y,uint8_t a);
