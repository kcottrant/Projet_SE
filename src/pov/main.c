// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "usart.h"

// interruption pour l'envoie de commandes USART 

ISR(USART0_RX_vect)
{
  unsigned char data;
  //Read the received data 
  data = UDR0;
  USART_Transmit(data);
}

void InitEffetHall(void)
{
  EIMSK &=~_BV(INT0);
  EICRA &=~ _BV(ISC00);
  EICRA |= _BV(ISC01);
  EIMSK |=_BV(INT0);
}

ISR(INT0_vect)
{
   USART_Transmit('a');
}


int main() {
  sei();
  // Lecture et écriture
  USART_Init(MYUBRR);
  //USART_Transmit('b');
  InitEffetHall();
  // Connexion SPI (communication avec les LED)
  SPI_MasterInit();

  volatile uint16_t i=1;

  while (i<=32768)
    {
      allumeLed(i);
      _delay_ms(400);
      if(i>=32768)
      {
	i=1;
	allumeLed(1);
	_delay_ms(400);
      }
      i=i*2;
    }

  // code ROMAIN
  /*

  	//attendre 3s, histoire que le moteur est en vitesse de croisière
	_delay(3000);
	//mesure vitesse pour commencer
	vitesse_angulaire_reele=measure_angular_speed();
	
	NB_TICKS_REMAIN= (1/6*vitesse_angulaire_reele - 256*(1/13000000))/(1/13000000); // ordre de grandeur = 225
	
    
	if( capteur effet hall detecte qqch)
		theta_real=0;
	

	// initialize timer
    timer0_init();
  
    // loop forever
    while(1)
    {
        // check if no. of overflows = 1
        if (tot_overflow_timr0 >= 1 )  // NOTE: '>=' is used
        {
            // check if the timer count reaches NB_TICKS_REMAIN -> dépendance de la vitesse réelle: NB_TICKS_REMAIN(vitesse_angulaire_reele)
            if (TCNT0 >= NB_TICKS_REMAIN)
            {
                TCNT0 = 0;            // reset counter
                tot_overflow_timr0 = 0;     // reset overflow counter
				theta_real++;
            }
		}
		//transmit ORDERs via SPI to driver
		transmit4displayLED(theta_real, t_en_s, t_en_min, t_en_h);
	}
    */
}


