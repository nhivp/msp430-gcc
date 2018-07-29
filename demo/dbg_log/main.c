/******************************************************************************
  file: main.c
  description: n/a
  Nhi Pham @ 2018
*******************************************************************************/
#include "msp430g2553.h"
#include "debug_log.h"

#define DCOCTL_REG_ADDR     0x056 /* DCO control register */
#define BCSCTL1_REG_ADDR    0x057 /* Basic clock system control 1 register*/

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    /* Load calibrated DCO vlues to set CPU clock to 1MHz */
    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    debug_init();

    /* Print a value of a register after configuring */
    debug_log("Register DCOCTL: ", DCOCTL);
    debug_log("Register BCSCTL1: ", BCSCTL1);

    return 0;
}