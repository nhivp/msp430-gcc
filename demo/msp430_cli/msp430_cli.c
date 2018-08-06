/*
 * File: msp430_cli.c
 * Description:
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include "msp_print.h"

int main(void)
{
    uart_init(0);

    msp_puts("Pham Van Nhi");

    while(1)
    {
        __no_operation();
        // __bis_SR_register(CPUOFF+GIE);

    }
}