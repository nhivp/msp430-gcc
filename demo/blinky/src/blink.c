//***************************************************************************************
//  file: blinky.c
//  description: Toggle Led P1.6
//  Nhi Pham @ 2018
//***************************************************************************************

#include <msp430g2553.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog timer
    P1DIR |= 0x40;                   // Set P1.6 to output direction

    for(;;)
    {
        volatile unsigned int i;    // volatile to prevent optimization

        P1OUT ^= 0x40;                // Toggle P1.6 using exclusive-OR

        i = 10000;                    // SW Delay
        while(i-- != 0);
    }

    return 0;
}
