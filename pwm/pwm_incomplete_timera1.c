#include <msp430.h>

#define TURN_CONST 5000
#define HALF_PERIOD 15000

void setLeftTurn() {
   TA1CCR1 = HALF_PERIOD - TURN_CONST;
   TA1CCR2 = HALF_PERIOD + TURN_CONST;
}
void setRightTurn() {
   TA1CCR1 = HALF_PERIOD + TURN_CONST;
   TA1CCR2 = HALF_PERIOD - TURN_CONST;
}
void setForward() {
   TA1CCR1 = HALF_PERIOD;     // CCR1 = wave 1 off time
   TA1CCR2 = HALF_PERIOD;     // CCR2 = wave 2 off time
}

void clockInit() {
   BCSCTL1 = CALBC1_16MHZ;
   DCOCTL = CALDCO_16MHZ;
}

void main(void) {

   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
   clockInit();               // 1 MHz

   P1DIR |= BIT2 + BIT1;      // P1.2, P1.1 output
   P1OUT &= ~(BIT2 + BIT1);   // init output, off

   TA1CCR1 = HALF_PERIOD;     // CCR1 = wave 1 off time
   TA1CCR2 = HALF_PERIOD;     // CCR2 = wave 2 off time
   TA1CCR0 = HALF_PERIOD * 2; // CCR0 = period

   TA1CCTL1 |= CCIE;          //enable interrupts when TAR = CCTL1
   TA1CCTL2 |= CCIE;          //enable interrupts when TAR = CCTL2
   TA1CCTL0 |= CCIE;          //enable interrupts when TAR = CCTL0

   TA1CTL = TASSEL_2 + MC_1;  // T_A, select 1MHz clock, up mode

   __bis_SR_register(GIE);

   while(1) {
      __delay_cycles(8000000);
      setForward();
      __delay_cycles(8000000);
      setLeftTurn();
      __delay_cycles(8000000);
      setRightTurn();
   }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void CCR0_detect (void) {
   P1OUT &= ~(BIT2 + BIT1);   // turn off p1.1 and p1.2
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A (void) {
   switch(TAIV) {
   case 2: P1OUT |= BIT1;     // turn on p1.1
         break;
   case 4: P1OUT |= BIT2;     // turn on p1.2
         break;
   }
}
