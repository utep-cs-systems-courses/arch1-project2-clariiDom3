#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"


static char curr_state = 0;
static char state = 1;

char toggle_red50()		/* led 50% intensity */
{
  switch (curr_state) {
  case 0:
    red_on = 1; //red is on
    curr_state = 1;
    break;
  case 1:
    red_on = 0; //red is off
    curr_state = 0;
    break;
  }
  led_update();		       
}

char toggle_red75()	/* led 75% intensity  */
{
  switch(curr_state){
  case 0:
    red_on = 1; //red on
    curr_state = 1;
    break;
  case 1:
    red_on = 1; //red is on
    curr_state = 2;
    break;
  case 2:
    red_on = 0; //red off
    curr_state = 0;
    break;
  }
  led_update();
}


void toggle_red25(){ /*led 25% intensity */
  switch(curr_state){
  case 0:
    red_on = 0; //red is off
    curr_state = 1;
    break;
  case 1:
    red_on = 0; //red is off
    curr_state = 2;
    break;
  case 2:
    red_on = 1; //red is on
    curr_state = 0;
    break;
  }
  led_update();
}


void dim(){
  static char state = 0;
  switch(state){
  case 0: //50%
    toggle_red50(); //on
    toggle_red50(); //off
    state = 1;
    break;
  case 1: //75%
    toggle_red75(); //on
    toggle_red75(); //on
    toggle_red75(); //off
    state = 2;
    break;
  case 2: //25%
    toggle_red25(); //off
    toggle_red25(); //off
    toggle_red25(); //on
    state = 0;
    break;
  }
}

void green_led_on(){ //turn green led on
  green_on = 1;
  red_on = 0;
  led_update();
}

void red_led_on(){ //turn red led on
  red_on = 1;
  green_on = 0;
  led_update();
}

void up_state(){ //determine up state
  state = 1;
  green_led_on();
}

void down_state(){ //determine down state
  state = 0;
  red_led_on();
}

void siren_state(){
  static char state = 0;
  switch(state){
  case 0:
  case 1: //tone decreases in first 2 cases
    up_state();
    state++;
    break;
  case 2: //tone decreases in last case
    down_state();
    state = 0;
  default:
    break;
  }
}

void buzzer_siren(){ //play siren
  static int x = 500;
  if(state){ //tone up if on up state
    x += 150;
  }
  else{ //tone down if on down state
    x -= 350;
  }
  short cycles = 2000000/x;
  buzzer_set_period(cycles);
}
