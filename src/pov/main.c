// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "spi.h"
#include "usart.h"
#include "timers.h"
#include "chiffres.h"
#include "chiffresDroits.h"
#include "aiguilles.h"

volatile uint8_t compteur_timer; // compte le nombre d'overflow du timer 1, au bout de 5, une seconde s'est écoulee

//compteurs pour l'heure qu'il est
volatile uint8_t compteur_h=11;
volatile uint8_t compteur_min=10;
volatile uint8_t compteur_sec=0;

volatile uint16_t vitesse=0; // vitesse moyenne de rotation
volatile uint16_t time1=0; // temps premier tour
volatile uint16_t time2=0; // temps deuxième tour
volatile uint8_t numero_cadran; // Cadran ou se trouve les LEDs 60 cadrans au total

// stockage des valeurs envoyés via USART
volatile uint8_t heurestemp[4];
volatile uint8_t compteur=0;

// mode d'affichage mode0 = aiguilles mode1=chiffres tordus mode2 : chiffres droits
volatile uint8_t mode = 0;

void miseAJourHeure(uint8_t heure)
{
  compteur_h=heure;
}

void miseAJourMin(uint8_t min)
{
  compteur_min=min;
}

void miseAJourSec(uint8_t sec)
{
  compteur_sec=sec;
}

// interruption pour l'envoie de commandes USART
ISR(USART0_RX_vect)
{
  unsigned char data;
  //Read the received data
  data = UDR0;
  // on doit envoyer sur l'USART : XXXXXX ou X : chiffre

  if((data=='h' && compteur==0))
  {
    compteur++;
  }
  //on recoit les dixaines des heures
  else if(compteur==1){
    compteur++;
    heurestemp[0]=data-48;//convertie char en int depuis code ASCII
  }
  //on recoit les unites des heures
  else if(compteur==2){
    compteur++;
    heurestemp[1]=data-48;
  }
  //on recoit les dixaines des minutes
  else if(compteur==3){
    compteur++;
    heurestemp[2]=data-48;
  }
  //on recoit les unites des minutes
  else if(compteur==4){
    compteur=0;
    heurestemp[3]=data-48;
    //met a jour l'heure
    compteur_h=heurestemp[0]*10+heurestemp[1];
    compteur_min=heurestemp[2]*10+heurestemp[3];
  }
  //mode aiguille
  else if (data=='a')
  {
    mode=0;
  }
  //mode chiffre tordu
  else if (data=='c')
  {
    mode=1;
  }
  //mode chiffre droit
  else if(data=='d')
  {
    mode=2;
  }
}


// TIMER1 overflow interrupt service routine
// called whenever TCNT0 overflows
// se produit 5 fois par seconde
// met a jour l'heure
ISR(TIMER1_COMPA_vect)
{
  compteur_timer ++;
  // keep a track of number of overflows
  if(compteur_timer==5)
  {
    compteur_timer=0;
    compteur_sec ++;
    if(compteur_sec==60)
    {
      compteur_min ++;
      compteur_sec = 0;
    }
    if(compteur_min==60)
    {
      compteur_h ++;
      compteur_min =0;
    }
    if(compteur_h==24)
    {
      compteur_h=0;
    }
  }
}


// interuption du timer 3
// se produit 60 fois par tour, met a jour le numero du cadran dan lequel se trouve la board
ISR(TIMER3_COMPA_vect)
{
  numero_cadran ++;
  if(numero_cadran==60)
  {
    numero_cadran = 0;
  }

}

//Initialisation de l'effet hall
void InitEffetHall(void)
{
  EIMSK &=~_BV(INT0);
  EICRA &=~ _BV(ISC00);
  EICRA |= _BV(ISC01);
  EIMSK |=_BV(INT0);
}

// interruption Effet Hall
// met a jour la vitesse moyenne de la board
ISR(INT0_vect)
{
  uint16_t vitesse2 = vitesse/60;
  OCR3AH = (vitesse2>>8);
  OCR3AL = vitesse2;
  numero_cadran=30;

  time1=time2;
  time2=TCNT1;
  int16_t difference=time2-time1;
  if(difference>0)
  {
    vitesse = (vitesse+time2-time1)/2;
  }
  else
  {
    vitesse = (vitesse +40625-time1+time2)/2;
  }
}

int main() {
  // enable les interuption globales
  sei();
  // Lecture et écriture
  USART_Init(MYUBRR);
  //USART_Transmit('b');
  InitEffetHall();
  // Connexion SPI (communication avec les LED)
  SPI_MasterInit();

  InitTimer1(compteur_timer);
  InitTimer3(vitesse);

  USART_Transmit('g');

  while(1){
    if(mode==0)
    {
      // Mode 0 : Aiguilles
      aiguilles(numero_cadran,compteur_h,compteur_min,compteur_sec);
    }
    else if(mode==1)
    {
      // Mode 1 : Chiffres tordus

      AfficheHeures(compteur_h,compteur_sec,numero_cadran);
      AfficheMinutes(compteur_min,compteur_sec,numero_cadran);

    }
    else if (mode==2){
      // Mode 2 : chiffres droits
      afficheHeure(numero_cadran, compteur_h, compteur_min,compteur_sec);
    }
  }
}
