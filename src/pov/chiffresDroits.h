#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void chiffreun(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
uint16_t calculCoeffDirect(uint16_t x1,uint8_t x2,uint16_t y1,uint16_t y2);
uint16_t calculOrdonOrigin(uint16_t x,uint8_t y,uint8_t a);
