#include <msp430.h>
#include <stdio.h>

#define SENSOR_NUM 8
#define SENSOR_READ BIT4

static volatile int sensorVal[SENSOR_NUM] = {0,0,0,0,0,0,0,0};

//Convert 8 bit binary with only one '1' to an integer
int conv_int(int input) {
   if(input == 0x01)
      return 0;
   else if(input == 0x02)
      return 1;
   else if(input == 0x04)
      return 2;
   else if(input == 0x08)
      return 3;
   else if(input == 0x10)
      return 4;
   else if(input == 0x20)
      return 5;
   else if(input == 0x40)
      return 6;
   else if(input == 0x80)
         return 7;
   else
      return -1;

}

void main() {
   WDTCTL = WDTPW + WDTHOLD;                               // Stop WDT
   ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;             // ADC10ON, interrupt enabled
   ADC10CTL1 = INCH_4;                                     // input A4 on 1.4
   ADC10AE0 |= BIT4;                                       // PA.4 ADC option select

   P2DIR = 0xFF;                                       //set pins to control decoder
   P2OUT = 0x01;
   P2SEL = 0x00;
   P2SEL2 = 0x00;
   TA1CCR0 = 250;                                          // PWM Period
   TA1CCTL0 = CCIE;                                           //

   TA1CTL = TASSEL_2 + MC_1 + ID_3;                         // SMCLK, up mode

   ADC10CTL0 |= ENC + ADC10SC;                 //change to timer1, nao plox
   ADC10CTL1 |=  ADC10DIV2;
   __bis_SR_register(GIE);

   while(1)
   {

   }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void) {                      //change to timer1, nao plox
   P2OUT = P2OUT << 1;
   if(!P2OUT) {                                 //lol
      P2OUT = 0x01;
   }

   ADC10CTL0 |= ADC10SC;
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
   sensorVal[conv_int(P2OUT)] = ADC10MEM;
   ADC10CTL0 &= ~ADC10IFG;
}

//cont convert and store in timer ISR
//set adc convert flag in timer asr then adc10sc in main if flag
