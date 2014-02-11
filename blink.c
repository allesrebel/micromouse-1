#include <stdio.h>
#include <msp430g2553.h>

unsigned int i = 0;                         // Initialize variables. This will keep count of how many cycles between LED toggles


int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer. This line of code is needed at the beginning of most MSP430 projects. 
                                            // This line of code turns off the watchdog timer, which can reset the device after a certain period of time.

  P1DIR |= 0x01;                            // P1DIR is a register that configures the direction (DIR) of a port pin as an output or an input. 


                                            // To set a specific pin as output or input, we write a '1' or '0' on the appropriate bit of the register.


                                            // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>


                                            // Since we want to blink the on-board red LED, we want to set the direction of Port 1, Pin 0 (P1.0) as an output

                                            // We do that by writing a 1 on the PIN0 bit of the P1DIR register
                                            // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
                                            // P1DIR = 0000 0001
                                            // P1DIR = 0x01     <-- this is the hexadecimal conversion of 0000 0001



  for (;;)                                  // This empty for-loop will cause the lines of code within to loop infinitely
    {



      P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR operation (^=)

      // P1OUT is another register which holds the status of the LED. 
      // '1' specifies that it's ON or HIGH, while '0' specifies that it's OFF or LOW
      // Since our LED is tied to P1.0, we will toggle the 0 bit of the P1OUT register



      for(i=0; i< 20000; i++);                // Delay between LED toggles. This for-loop will run until the condition is met. 
      //In this case, it will loop until the variable i increments to 20000.
    }
  return 0;
}
