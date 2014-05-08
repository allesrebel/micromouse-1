#include <msp430.h>

#define SENSOR_NUM 8
#define SENSOR_READ BIT4

static volatile int sensorVal[SENSOR_NUM];

int main(void) {
  WDTCTL = WDTPW + WDTHOLD;                               // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;             // ADC10ON, interrupt enabled
  ADC10CTL1 = INCH_4;                                     // input A4 on 1.4
  ADC10AE0 |= SENSOR_READ;                                // PA.4 ADC option select

  P2DIR |= BIT0 + BIT1 + BIT2;			          //set pins to control decoder

  CCR0 = 250;                                             // PWM Period                                         /*CHANGE ME TO TIMER1*/
  CCTL0 = CCIE;                                           //							/*CHANGE ME TO TIMER1*/

  TACTL = TASSEL_2 + MC_1 + TAIE + ID_3;                  // SMCLK, up mode  					/*CHANGE ME TO TIMER1*/

  ADC10CTL0 |= ENC + ADC10SC + ADC10DIV2;                 //change to timer1, nao plox
  __bis_SR_register(GIE);
  for (;;) {

    }
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void ta0cc0_isr (void) {                      //change to timer1, nao plox
  P2OUT++;

  if((P2OUT & 0x07) == SENSOR_NUM)
    {
      P2OUT &= ~(BIT0 + BIT1 + BIT2);
    }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  sensorVal[P2OUT & 0x07] = ADC10MEM;
  ADC10CTL0 &= ~ADC10IFG;
  ADC10CTL0 |= ENC + ADC10SC;
}


