#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void chiffreun(uint8_t numero_cadran);
uint8_t calculLedAllume(int taba[11],int tabb[11], uint16_t posLedx, uint16_t posLedy,uint16_t tabchiffrex[12],uint16_t tabchiffrey[12], uint8_t *estNull);
uint16_t convertToDecimal(uint8_t tabled[16]);
int calculCoeffDirect(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2,uint8_t *estNull);
int calculOrdonOrigin(uint16_t x,uint16_t y,int a,uint8_t *estNull);
