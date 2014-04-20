#include <msp430.h> 

// 2 wave output, but no duty cycle control
// if someone can figure out how to do this with only 1 timer...

#define DELTA 500
#define LEFT 0
#define RIGHT 1
#define FORWARD 2

static volatile int direction;
static volatile int wave1;

void setLeftTurn() {
   direction = LEFT;
}
void setRightTurn() {
   direction = RIGHT;
}
void setForward() {
   direction = FORWARD;
}
void turnLeft() {
   if(wave1) {
      P1OUT &= ~BIT1;      // Reset P1.1
      TA1CCR1 += DELTA;    // Prepare for second wave (by adding delta)
      wave1 = 0;           // Set wave1 flag low
   }
   else {
      P1OUT &= ~BIT2;      // Reset P1.2
      TA1CCR1 += 0-DELTA;  // Return for first wave (by removing delta)
      wave1 = 1;           // Set wave1 flag high
   }
}
void turnRight() {
   if(wave1) {
      P1OUT &= ~BIT2;      // Reset P1.2
      TA1CCR1 += DELTA;    // Prepare for second wave (by adding delta)
      wave1 = 0;           // Set wave1 flag low
   }
   else {
      P1OUT &= ~BIT1;      // Reset P1.1
      TA1CCR1 += 0-DELTA;  // Return for first wave (by removing delta)
      wave1 = 1;           // Set wave1 flag high
   }
}
void goForward() {
   P1OUT ^= BIT1 + BIT2;
}

void main(void) {

   WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

   P1DIR |= BIT2 + BIT1;      // P1.1, P1.2 output
   TA1CTL = TASSEL_1 + MC_1;   // T_A, select smclk, up mode
   TA1CCTL1 |= CCIE;             // CCR1 interrupt enabled
   TA1CCTL2 |= OUTMOD_7 + CCIE;  // CCR2, set/reset mode

   //P1OUT &= ~(BIT2 + BIT1);

   TA1CCR1 = 1000;               // CCR1 = on time
   TA1CCR2 = 2000;               // CCR2 = period

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

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A (void) {
   switch(TA1IV) {
      case 2:  if(direction == LEFT) {
                  turnLeft();
               } else if (direction == RIGHT) {
                  turnRight();
               } else {
                  goForward();
               }
               break;
      default: P1OUT |= BIT1 + BIT2;   // Set both
               break;
   }
}