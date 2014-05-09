#include <msp430.h> 
#define RST_ALL_ENC 10
#define ENC0 0
#define ENC5 5
#define ENC6 6
#define ENC7 7

volatile int encoder0, encoder5 = 0; 
volatile int encoder6, encoder7 = 0;
//named after the pins that they're attached to

void encoderInit() {
   P1DIR &= ~(BIT0 + BIT5 + BIT6 + BIT7);
   P1REN |= BIT0 + BIT5 + BIT6 + BIT7;
   P1IE |= BIT0 + BIT5 + BIT6 + BIT7;
   __enable_interrupts();
}
void encoderReset(int encoderBit) {
   switch(encoderBit) {
      case 0: encoder0 = 0;
      case 5: encoder5 = 0;
      case 6: encoder6 = 0;
      case 7: encoder7 = 0;
      case RST_ALL_ENC: encoder7 = encoder6 = encoder5 = encoder7 = 0;
   }
}
void main() {
	while(1);
}
#pragma vector=PORT1_VECTOR
__interrupt void falling_edge_capture() {  // captures falling edge from encoder wave
	if(P1IFG & BIT0) {    // if button interrupt is on BIT0,
		encoder0++;        // increment encoder0 count
      P1IFG &= ~BIT0;    // clear interrupt flag for BIT0
	} else if(P1IFG & BIT5) {
      encoder5++;
      P1IFG &= ~BIT5;
   } else if(P1IFG & BIT6) {
      encoder6++;
      P1IFG &= ~BIT6;
   } else if(P1IFG & BIT7) {
      encoder7++;
      P1IFG &= ~BIT7;
   }
}
