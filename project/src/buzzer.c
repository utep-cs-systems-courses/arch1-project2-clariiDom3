#include <msp430.h>
#include "buzzer.h"
#include "libTimer.h"


#define A3 2278
#define G3 2551
#define C3 3846
#define E4 1517
#define C4 1911
#define G4 1276
#define E3 3033
#define B3 2025


void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void buzzer_off(){
  buzzer_set_period(0);
}

void mario_song(){
  int notes[] = {E4,E4,E4,C4,E4,G4,G3,C4,G3,E3,A3,B3,A3,A3};
  int i = 0;
  while(i < sizeof(notes)){
    int count = 0;
    while(count < 20){
      int count2 = 0;
      while(count2 < 30000){
	count2++;
      }
      count++;
    }
    buzzer_set_period(notes[i]);
    //    state_advance();
    i++;
  }
}
