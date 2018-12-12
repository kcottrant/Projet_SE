#include "display.h"

//	http://jmfriedt.free.fr/projet_POV2015.pdf
//	https://telefab.fr/2013/06/16/persistance-retinienne-et-affichage-dimage-3d/
//	http://nononux.free.fr/index.php?page=elec-brico-pic-pov


// global variable to count the real time actual theta
volatile uint8_t theta_real;
volatile uint8_t tot_overflow_timr0;
volatile int NB_TICKS_REMAIN;

volatile int t_50ms;
volatile int t_en_s;
volatile int t_en_min;
volatile int t_en_h;
  
const int nb_ANGLES_TOTAL = 360;	//ou 160 peut etre, ou plus, a voir....
 
const char aiguilles[5] = 
{
0b1111111100000000,	// mins
0b1111111111111000,	// hours
0b0000000000000100,	//déco
0b0000000000000010,	// secs
0b0000000000000001,	//déco
};  

float measure_angular_speed(){
  /*
   struct donnees_mesure {
	uint8_t t_old=0;
	uint8_t t=0;
	};
  
  while (donnees_mesure.t_old== 0 || donnees_mesure.t==0){
  //1ère interruption HALL: lire valeur compteur: i
  //donnees_mesure.t=i;
  
  //2ème interruption HALL: lire valeur compteur: i
  //donnees_mesure.t_old=donnees_mesure.t;
  //donnees_mesure.t=i;
  }
  
  int v_ang = L_BARRE * 360/(donnees_mesure.t_old - donnees_mesure.t);	//vitesse angulaire
  return (v_ang);
*/
}


 
void transmit4displayLED(int theta, int sec, int min, int hour){
	
	//valeur à transmettre:
	int theta_hour_timer = hour*30 -180;

	int theta_min_timer = min*6 -180;

	int theta_sec_timer = sec*6 -180;
	
	
	char valeur_trans;
	if(theta == theta_hour_timer){
	      valeur_trans= aiguilles[2];
	}
	if(theta == theta_min_timer){
		valeur_trans |= aiguilles[1];
	}
	if( 0 <= theta <= theta_sec_timer){
		valeur_trans |= aiguilles[4];
	}
	if((theta == 0) || (theta == 22.5) || (theta == 45) || (theta == 67.5) || (theta == 90) || (theta == 112.5) || (theta == 135)  || (theta == 157.5)  || (theta == 180)  || (theta == 202.5)  || (theta == 225)  || (theta == 247.5)  || (theta == 270)  || (theta == 292.5)  || (theta == 315)  || (theta == 337.5)  || (theta == 360)){
		valeur_trans |= ((valeur_trans & aiguilles[4]) >> 1) ^ aiguilles[5];
	}
	if((theta == 0) || (theta == 90) || (theta == 180) || (theta == 270) || (theta == 360)){
		valeur_trans |= aiguilles[3];
	}
	
	//peut-être utiliser une fonction d'adaptation
	
	//transmit via SPI
}
  
void timer0_init()
{
    // set up timer with prescaler  
	TCCR0 |= (1 << CS00);	// no prescaler
	
    // initialize counter
    TCNT0 = 0;
	// enable overflow interrupt
    TIMSK |= (1 << TOIE0);
 
    // enable global interrupts
    sei();

	tot_overflow_timr0 = 0;
}


