#include <msp430.h>
#include <stdio.h>
#include <math.h>

#define SENSOR_NUM 8
#define SENSOR_READ BIT4

static volatile int sensorVal[SENSOR_NUM];

//Convert 8 bit binary with only one '1' to an interger
int conv_int(int input) {
  int temp = input;
  int i;
  for(i = 0; temp != 0x01; i++) {
    temp = temp >> 1;
  }
  return i;
}

int main() {
  WDTCTL = WDTPW + WDTHOLD;                               // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;             // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_4;                                     // input A4 on 1.4
  ADC10AE0 |= BIT4;                                       // PA.4 ADC option select

  P2DIR = 0xFF;		                                  //set pins to control decoder
  P2SEL = 0x00;
  P2SEL2 = 0x00;
  CCR0 = 250*8;                                           // PWM Period                                         /*CHANGE ME TO TIMER1*/
  CCTL0 = CCIE;                                           //							/*CHANGE ME TO TIMER1*/

  TACTL = TASSEL_2 + MC_1 + TAIE;                         // SMCLK, up mode  				        /*CHANGE ME TO TIMER1*/

  ADC10CTL0 |= ENC + ADC10SC + ADC10DIV2;                 //change to timer1, nao plox
  __bis_SR_register(GIE);

  for(;;) {
  }
return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void ta0cc0_isr (void) {                      //change to timer1, nao plox
 if(P2OUT == 0x80) {
    P2OUT = 0x01;
    }
 else {
   P2OUT = P2OUT << 1;
 }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
  sensorVal[conv_int(P2OUT)] = ADC10MEM;
  ADC10CTL0 &= ~ADC10IFG;
  ADC10CTL0 |= ENC + ADC10SC;
}
