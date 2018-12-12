// En-têtes fournies par AVR pour les
// registres
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//#define FOSC 1843200// Clock Speed
#define FOSC 13000000// Clock Speed
//1843200
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

//	https://gist.github.com/Wollw/2381139
//	http://maxembedded.com/2011/06/avr-timers-timer0/
//	https://maxembedded.wordpress.com/2011/06/22/introduction-to-avr-timers/
// (http://maxembedded.com/2011/06/avr-timers-timer1/)
//	https://maxembedded.wordpress.com/2011/06/24/avr-timers-timer0-2/

volatile int t_50ms;
volatile int t_en_s;
volatile int t_en_min;
volatile int t_en_h;

// global variable to count the number of overflows
volatile uint8_t tot_overflow;
  
  
  
// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER1_OVF_vect)
{
    // keep a track of number of overflows
    tot_overflow++;
}

unsigned int TIM16_ReadTCNT1( void )
{
unsigned char sreg;
unsigned int i;
/* Save global interrupt flag */
sreg = SREG;
/* Disable interrupts */
__disable_interrupt();
/* Read TCNT1 into i */
i = TCNT1;
/* Restore global interrupt flag */
SREG = sreg;
__enable_interrupt(); /* set global interrupt enable */
return i;
}

void TIM16_WriteTCNT1( unsigned int i )
{
unsigned char sreg;
unsigned int i;
/* Save global interrupt flag */
sreg = SREG;
/* Disable interrupts */
__disable_interrupt();
/* Set TCNT1 to i */
TCNT1 = i;
/* Restore global interrupt flag */
SREG = sreg;
__enable_interrupt(); /* set global interrupt enable */
}

void timer1_init()
{
    // set up timer with prescaler = 256
	TCCR1 |= (1 << CS12);	//TCCR1 |= (1 << CS12)|(1 << CS10);  //(prescaler = 1024)  
  
    // initialize counter
    TCNT1 = 0;
	// enable overflow interrupt
    TIMSK |= (1 << TOIE1);
 
    // enable global interrupts
    sei();
	
	t_50ms=0;
	t_en_s=0;
	t_en_min=0;
	t_en_h=0;
	
	tot_overflow = 0;
}


int main(void)
{
  
    // initialize timer
    timer1_init();
  
    // loop forever
    while(1)
    {
        // check if no. of overflows = 9
        if (tot_overflow >= 9)  // NOTE: '>=' is used
        {
            // check if the timer count reaches 254
            if (TCNT1 >= 254)
            {
                TCNT1 = 0;            // reset counter
                tot_overflow = 0;     // reset overflow counter
				t_50ms = t_50ms + 1;
            }
		}
		//reupdate actual time
		if (t_50ms >= 20){  //	car:   1/(50*10^-3)=20
			t_50ms=0;
			t_en_s = t_en_s + 1;
		}
		if (t_en_s >= 60){
			t_en_s=0;
			t_en_min = t_en_min + 1;
		}
		if (t_en_min >= 60){
			t_en_min=0;
			t_en_h = t_en_h + 1;
		}
		if (t_en_h >= 24){
			t_en_h=0;
		}
			
		printf("sec %d, min %d, hours %d", t_en_s, t_en_min, t_en_h);
	}
}



