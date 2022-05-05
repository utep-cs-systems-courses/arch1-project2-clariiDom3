#ifndef switches_included
#define switches_included

//switches on msp
#define SW1 BIT0 //P2.0  
#define SW2 BIT1 //p2.1
#define SW3 BIT2 //p1.2
#define SW4 BIT3 //p0.3

#define SWITCHES (SW1 | SW2 | SW3 | SW4) //SWITCHES ON BOARD

void switch_init();
void switch_interrupt_handler();

extern char button_state;



#endif
