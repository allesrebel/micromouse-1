#include <msp430.h> 

// 2 wave output, but no duty cycle control
// if someone can figure out how to do this with only 1 timer...

#define DELTA 500

int direction;

void setLeftTurn() {
   direction = 0;
}
void setRightTurn() {
   direction = 1;
}
void setForward() {
   direction = 2;
}

void main(void) {

   WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
   
   P1DIR |= BIT1 + BIT2;      // P1.1, P1.2 output
   TA1CTL = TASSEL_1 + MC_1;   // T_A, select smclk, up mode
   TA1CCTL1 |= CCIE;             // CCR1 interrupt enabled
   TA1CCTL2 |= OUTMOD_7 + CCIE;  // CCR2, set/reset mode

   TA1CCR1 = 1000;               // CCR1 = on time, CCR2 = off time
   TA1CCR2 = 1000;               // CCR2 + CCR1 = Period

   while(1) {
      __delay_cycles(8000000);
      setLeftTurn();
      __delay_cycles(8000000);
      setRightTurn();
      __delay_cycles(8000000);
      setForward();
   }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {
   if(direction == 0) {        // left turn
      switch(TA1IV) {
         case 2:  P1OUT ^= BIT1;       // Toggle P1.1
                  TA1CCR1 += DELTA;     // Prepare for second wave
                  break;
         case 4:  P1OUT ^= BIT2;       // Toggle P1.2
                  TA1CCR1 += -DELTA;   // Reset for first wave
                  break;
         default: P1OUT ^= BIT1 + BIT2;
                  break;
      }
   }
   else if(direction == 1) {        // right turn
      switch(TA1IV) {
         case 2:  P1OUT ^= BIT2;       // Toggle P1.2
                  TA1CCR1 += DELTA;     // Prepare for second wave
                  break;
         case 4:  P1OUT ^= BIT1;       // Toggle P1.1
                  TA1CCR1 += -DELTA;   // Reset for first wave
                  break;
         default: P1OUT ^= BIT1 + BIT2;
                  break;
      }
   }
   else {                     // forward
      P1OUT ^= BIT1 + BIT2;
   }
}
