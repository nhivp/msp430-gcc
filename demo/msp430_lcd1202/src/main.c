/*
 * Created by nhivp on 19/08/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include <stdint.h>
#include "msp430g2553.h"
#include "hal_lcd.h"
/**
 *  Typedef definition
 */

/**
 *  Macro definition
 */

/**
 * Private function prototypes
 */
static void board_init(void);

/**
 *  Private variables
 */

/**
 *  Exported variables
 */

/**
 * Main App
 */
int main(void)
{
    board_init();
    lcd_init();

    lcd_printc('x');

    while (1)
    {

    }
}

/**
 * Initialize the board MSP430G2 LaunchPad
 */
static void board_init(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    /* Load calibrated DCO vlues to set CPU clock to 1MHz */
    BCSCTL1 = CALBC1_1MHZ;    // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;     // Set DCO to 1MHz
}
