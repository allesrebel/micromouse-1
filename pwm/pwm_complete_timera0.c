#include <msp430.h>

#define TURN_CONST 5000
#define HALF_PERIOD 17900
#define F_COMP 500

void moveLeft();
void moveRight();   
void forward();     // calibrate me with f_comp
void stop();        // i'm good
void slow();        // lower pwm
void invertHigh();  // set invert high
void invertLow();   // set invert low
void left90();      // turn profile, not written yet
void right90();     // turn profile, not written yet
void left45();      // turn profile, not written yet
void right45();     // turn profile, not written yet
void clockInit();   
void timerA0Init();

void main(void) {

   clockInit();
   timerA0Init();

   // WRITE YOUR CODE BELOW HERE IN WHILE LOOP!! AVAIALBE FUNCTIONS ARE ABOVE
   // IF YOU REALLY NEED TO, MODIFY THE FUNCTIONS BELOW

   while(1) {      
      forward();
   }
}

void moveLeft() {
   TA0CCR1 = HALF_PERIOD - TURN_CONST;
   TA0CCR2 = HALF_PERIOD + TURN_CONST;
}
void moveRight() {
   TA0CCR1 = HALF_PERIOD + TURN_CONST;
   TA0CCR2 = HALF_PERIOD - TURN_CONST;
}
void forward() {
   TA0CCR1 = HALF_PERIOD + COMPENSATION;     // CCR1 = wave 1 off time
   TA0CCR2 = HALF_PERIOD - COMPENSATION;     // CCR2 = wave 2 off time
}
void stop() {
   TA0CCR1 = HALF_PERIOD * 2 + 10;  // CCR1 > CCR0, never on
   TA0CCR2 = HALF_PERIOD * 2 + 10;  // CCR2 > CCR0, never on
}
void slow() {
   TA0CCR1 = 2*HALF_PERIOD - 1000;
   TA0CCR2 = 2*HALF_PERIOD - 1010;
}
void invertHigh() {
   P1OUT |= BIT3;
}
void invertLow() {
   P1OUT &= ~BIT3;
}
void left90() {

}
void right90() {

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
   WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

   P1DIR |= BIT3 + BIT2 + BIT1; // P1.3, P1.2, P1.1 output
   P1OUT &= ~(BIT2 + BIT1);   // init output, off

   TA0CCR1 = HALF_PERIOD;     // CCR1 = wave 1 off time
   TA0CCR2 = HALF_PERIOD;     // CCR2 = wave 2 off time
   TA0CCR0 = HALF_PERIOD * 2; // CCR0 = period

   TA0CCTL1 |= CCIE;          //enable interrupts when TAR = CCTL1
   TA0CCTL2 |= CCIE;          //enable interrupts when TAR = CCTL2
   TA0CCTL0 |= CCIE;          //enable interrupts when TAR = CCTL0

   TA0CTL = TASSEL_2 + MC_1;  // T_A, select 16MHz clock, up mode

   __bis_SR_register(GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void CCR0_detect (void) {
   P1OUT &= ~(BIT2 + BIT1);   // turn off p1.1 and p1.2
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void CCR1_CCR2_detect (void) {
   switch(TAIV) {
   case 2: P1OUT |= BIT1;     // turn on p1.1
         break;
   case 4: P1OUT |= BIT2;     // turn on p1.2
         break;
   }
}
