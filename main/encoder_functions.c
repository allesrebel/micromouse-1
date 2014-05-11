#include <msp430.h> 
#include "micromouse.h"

#define RST_ALL_ENC 10
#define ENC0 0
#define ENC5 5
#define ENC6 6
#define ENC7 7

volatile int encoder0 = 0;
volatile int encoder5 = 0; 
volatile int encoder6 = 0; 
volatile int encoder7 = 0;
//named after the pins that they're attached to

void encoderInit() {
  P1DIR &= ~(BIT0 + BIT5 + BIT6 + BIT7);
  P1REN |= BIT0 + BIT5 + BIT6 + BIT7;
  P1IE |= BIT0 + BIT5 + BIT6 + BIT7;
  __bis_SR_register(GIE);
}

void encoderReset(int encoderBit) {
  switch(encoderBit) {
  case ENC0: encoder0 = 0;
  case ENC5: encoder5 = 0;
  case ENC6: encoder6 = 0;
  case ENC7: encoder7 = 0;
  case RST_ALL_ENC: encoder0 = encoder6 = encoder5 = encoder7 = 0;
  }
}
