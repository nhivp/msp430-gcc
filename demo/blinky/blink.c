/***************************************************************************************
  file: blinky.c
  description: Toggle Led P1.6
  Nhi Pham @ 2018
***************************************************************************************/

#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        /* Stop watchdog timer */
    P1DIR |= 0x40;                   /* Set P1.6 to output direction */

    for(;;)
    {
        P1OUT ^= 0x40;                /* Toggle P1.6 using exclusive-OR */

        /* Wait for 200000 cycles */
        __delay_cycles(200000);
    }
}
