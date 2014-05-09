#include <msp430.h>

#define TURN_CONST 7500
#define HALF_PERIOD 15000   // DO NOT TOUCH ME!!! (I AM AT 15000)
#define FAST_CALIB 400

void moveRight();             // do not use
void moveLeft();              // do not use
void forward();             // 40% duty
void stop();                // 0% duty
void easeStop();              // do not use! has _delay_cycles()
void slow();                // 25% duty
void fast();                  // do not use
void torque();              // full speed, only use to start motors
void invertHigh();          // set invert high
void invertLow();           // set invert low
void left90();              // turn profile, test me
void right90();             // turn profile, test me
void left45();                // turn profile, not written yet
void right45();               // turn profile, not written yet
void clockInit();           // always use me before timerA0Init
void timerA0Init();         // make sure to init the timer!
void motorInit();           // i'm just the two above, in order!!

void main(void) {

   motorInit();

   stop();
   __delay_cycles(32000000);

   while(1) {
      moveRight();
      __delay_cycles(7500000);
      stop();
      __delay_cycles(32000000);
      moveLeft();
      __delay_cycles(7500000);
      stop();
      __delay_cycles(32000000);
   }

}

void moveRight() {
   TA0CCR1 = TURN_CONST;
   TA0CCR2 = HALF_PERIOD + 100;
}
void moveLeft() {
   TA0CCR1 = HALF_PERIOD + 100;
   TA0CCR2 = TURN_CONST;
}
void forward() {
   TA0CCR1 = HALF_PERIOD * 0.4;     // CCR1 = wave 1 off time
   TA0CCR2 = HALF_PERIOD * 0.4;     // CCR2 = wave 2 off time
}
void stop() {
   TA0CCR1 = HALF_PERIOD * 2 + 10;  // CCR1 > CCR0, never on
   TA0CCR2 = HALF_PERIOD * 2 + 10;  // CCR2 > CCR0, never on
}
void easeStop() {
   slow();
   __delay_cycles(2000000);
   stop();
}
void slow() {
   TA0CCR1 = HALF_PERIOD + HALF_PERIOD/2;
   TA0CCR2 = HALF_PERIOD + HALF_PERIOD/2;
}
void fast() {
   TA0CCR1 = HALF_PERIOD - 2000 - FAST_CALIB;
   TA0CCR2 = HALF_PERIOD - 2000;
}
void torque() {
   TA0CCR1 = HALF_PERIOD/3000;
   TA0CCR2 = HALF_PERIOD/3000 + 10;
}
void invertHigh() {
   P1OUT |= BIT3;
}
void invertLow() {
   P1OUT &= ~BIT3;
}
void left90() {
   moveLeft();
   __delay_cycles(7500000);
   stop();
   __delay_cycles(32000000);
}
void right90() {
   moveRight();
   __delay_cycles(7500000);
   stop();
   __delay_cycles(32000000);
}
void left45() {

}
void right45() {

}
void clockInit() {
   BCSCTL1 = CALBC1_16MHZ;
   DCOCTL = CALDCO_16MHZ;
}
void timerA0Init() {
   WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

   P1DIR |= BIT3 + BIT2 + BIT1;  // P1.3, P1.2, P1.1 output
   P1OUT &= ~(BIT2 + BIT1);      // init output, off

   TA0CCR1 = HALF_PERIOD;        // CCR1 = wave 1 off time
   TA0CCR2 = HALF_PERIOD;        // CCR2 = wave 2 off time
   TA0CCR0 = HALF_PERIOD * 2;    // CCR0 = period

   TA0CCTL1 |= CCIE;             //enable interrupts when TAR = CCTL1
   TA0CCTL2 |= CCIE;             //enable interrupts when TAR = CCTL2
   TA0CCTL0 |= CCIE;             //enable interrupts when TAR = CCTL0

   TA0CTL = TASSEL_2 + MC_1;     // T_A, select 16MHz clock, up mode

   __bis_SR_register(GIE);

   invertHigh();
}
void motorInit() {
   clockInit();
   timerA0Init();
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void ccr0_clear_pulse (void) {
   P1OUT &= ~(BIT2 + BIT1);      // turn off p1.1 and p1.2
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void ccr1_2_set_pulse (void) {
   switch(TAIV) {
   case 2: P1OUT |= BIT1;        // turn on p1.1 (left motor)
         break;
   case 4: P1OUT |= BIT2;        // turn on p1.2 (right motor)
         break;
   }
}
