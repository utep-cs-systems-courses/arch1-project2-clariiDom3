#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

char button_state = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;
  count++;
  if((count % 60) == 0 && button_state == 0){
    mario_song();
    count = 0;
  }
  else if((count % 25) == 0 && button_state == 1)
    buzzer_siren();
  else if((count % 62) ==0 && button_state ==1){
    siren_state();
    count = 0;
  }
  else if(button_state == 2){
    buzzer_set_period(0);
    green_led_on();
    count = 0;
  }
  else if((count % 100) && button_state == 3){
    buzzer_set_period(0);
    dim();
    count = 0;
  }
}