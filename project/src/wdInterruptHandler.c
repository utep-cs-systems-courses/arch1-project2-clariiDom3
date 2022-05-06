#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

char button_state = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;
  // count++;

  //switch 1
  if((count++ == 105) == 0 && button_state == 0){ //button 1, plays song
    mario_song(); //play song
    count = 0;
  }
  //switch 2
  else if((count % 25) == 0 && button_state == 1) //butto9n 2, siren buzz
    buzzer_siren(); //produce siren buzz
  else if((count == 62) && button_state ==1){ //advances siren state, switched to leds
    siren_state(); //control tone
    count = 0;
  }
  //switch 3
  else if(button_state == 2){ //button 3, only green led on, buzzer off
    buzzer_off(); //turn buzzer off
    green_led_on(); //turn green led on
  }
  //switch 4
  else if((count == 3) && button_state == 3){ //buzzer 4, red led brightly & dimming
    // buzzer_set_period(0);
    red_led_on();
    dim();
    count = 0;
  }
}
