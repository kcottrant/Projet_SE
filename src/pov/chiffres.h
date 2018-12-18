#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void Affichezero(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes);
void Afficheun(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichedeux(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichetrois(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichequatre(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichecinq(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichesix(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichesept(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void Affichehuit(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes);
void Afficheneuf(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas);
void AfficheHeures(uint8_t heures,uint8_t secondes,uint8_t numero_cadran);
void AfficheMinutes(uint8_t minutes,uint8_t secondes,uint8_t numero_cadran);

