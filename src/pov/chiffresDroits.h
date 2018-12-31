#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void afficheHeure(uint8_t numero_cadran,uint8_t heure,uint8_t minute);
void chiffre(uint8_t chiffre,uint8_t quart);
uint8_t calculLedAllume(int *taba,int *tabb, uint16_t posLedx, uint16_t posLedy,int16_t *tabchiffrex1,int16_t *tabchiffrex2 ,int16_t *tabchiffrey1, int16_t *tabchiffrey2, uint8_t *estNull, uint8_t tailleTabDroite,uint16_t moinsX, uint16_t moinsY);
uint8_t miseAZeroPointeurs(uint8_t chiffre,int *ptaba, int *ptabb, uint8_t * pcoeffEstNull, int *ptabaSauv, int *ptabbSauv, uint8_t *pcoeffNullSauv);
uint16_t convertToDecimal(uint8_t tabled[16]);
void calculDroites(int16_t *pchiffrex1,int16_t *pchiffrex2,int16_t *pchiffrey1,int16_t *pchiffrey2,uint8_t *pCoeffNull, int *ptaba, int *ptabb, uint8_t tailleTabDroite, uint16_t moinsX, uint16_t moinsY);
int calculCoeffDirect(int16_t x1,int16_t x2,int16_t y1,int16_t y2,uint8_t *estNull);
int calculOrdonOrigin(int16_t x,int16_t y,int a,uint8_t *estNull);
