// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "spi.h"
#include "usart.h"
#include "display.h"
#include "chiffres.h"
#include "chiffresDroits.h"

volatile uint8_t compteur_timer; // compte le nombre d'overflow du timer 1, au bout de 5, une seconde s'est écoulee

//compteurs pour l'heure qu'il est
volatile uint8_t compteur_h=4; 
volatile uint8_t compteur_min=57;
volatile uint8_t compteur_sec=0;

volatile uint16_t vitesse=0; // vitesse moyenne de rotation
volatile uint16_t time1=0; // temps premier tour
volatile uint16_t time2=0; // temps deuxième tour
volatile uint8_t numero_cadran;
volatile uint16_t leds;

// stockage des valeurs envoyés via USART
volatile unsigned char heurestemp[3];
volatile uint8_t compteur=0;

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
  
  if((data=='h' && compteur==0)||compteur>0)
  {
    heurestemp[compteur]=data;
    //char buffer[16];
    //sprintf(buffer,"%i \n\r",(uint8_t)atoi(*heurestemp[compteur]));
    //USART_puts(buffer);
    compteur++;
    if(compteur==3)
    {
      USART_Transmit('f');
      compteur=0;
      miseAJourHeure((uint8_t)heurestemp[1]*10+(uint8_t)heurestemp[2]);
    }
  }
}

//mode d'affichage aiguille
void aiguilles(void){
  uint8_t heure12;
  while(1)
  {
    if(compteur_h>=12){
      heure12=compteur_h-12;
    }
    else{
      heure12=compteur_h;
    }
    //sec min pas h
    if(numero_cadran==compteur_sec && numero_cadran==compteur_min)// &&  numero_cadran/5!=heure12)
    {
       allumeLed(49151);
    }
    //sec min h
    else if(numero_cadran==compteur_sec && numero_cadran==compteur_min &&  numero_cadran/5==heure12 && numero_cadran%5==0)
    {
       allumeLed(48895);
    }
    //sec pas min pas h
    else if (numero_cadran==compteur_sec && numero_cadran!=compteur_min)//&& numero_cadran/5!=heure12)
    {
      allumeLed(32768);
    }
    //sec pas min h
    else if (numero_cadran==compteur_sec && numero_cadran!=compteur_min && numero_cadran/5==heure12 &&  numero_cadran%5==0)
    {
      allumeLed(33023);
    }
    //pas sec min pas h
    else if(numero_cadran!=compteur_sec && numero_cadran==compteur_min)// && numero_cadran/5!=heure12)
    {
      allumeLed(16383);
    }
    //pas sec min h
    else if(numero_cadran!=compteur_sec && numero_cadran==compteur_min && numero_cadran/5==heure12 &&  numero_cadran%5==0)
    {
      allumeLed(16127);
    }
    //pas sec pas min h
    else if(numero_cadran!=compteur_sec && numero_cadran!=compteur_min && numero_cadran/5==heure12 &&  numero_cadran%5==0)
    {
      allumeLed(255);
    }
    else
    {
       allumeLed(0);
    }
  }
}

// TIMER0 overflow interrupt service routine
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
  //char buffer[16];
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
  //volatile uint16_t i=1;
  USART_Transmit('g');

  // Mode aiguilles activé
  //aiguilles();
  /*  while(1)
  {
    AfficheHeures(compteur_h,compteur_sec,numero_cadran);
    AfficheMinutes(compteur_min,compteur_sec,numero_cadran);
    }*/
  while(1)
    {
      chiffreun(numero_cadran);
    }
}


