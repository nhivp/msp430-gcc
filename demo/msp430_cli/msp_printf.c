/*
 * File: msp_print.c
 * Description:
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include "msp_print.h"

/**
 * Private prototype functions
 **/
void msp_putc(unsigned char character);

void uart_init(uint16_t baudrate)
{
    /* Configure hardware UART */
    P1SEL = BIT1 + BIT2 ;  // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;  // Use SMCLK
    UCA0BR0 = 104;         // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
    UCA0BR1 = 0;           // Set baud rate to 9600 with 1MHz clock
    UCA0MCTL = UCBRS0;     // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;  // Initialize USCI state machine
    IE2 |= UCA0RXIE;       // Enable USCI_A0 RX interrupt
    // msp_putc('N');
}

void msp_printf(char *format, ...)
{

}

/**
 * Sends a single byte out through UART
 **/
void msp_putc(unsigned char character)
{
    while (!(IFG2 & UCA0TXIFG)); // USCI_A0 TX buffer ready?
    UCA0TXBUF = character; // TX -> RXed character
}

void msp_puts(char* s)
{
    while (*s != '\0')
    {
        msp_putc(*s);
        s++;
    }
}

/**************************************************
 * USCI0RX_ISR Interrupt Handler
 **************************************************/
// __attribute__ ((interrupt(USCIAB0RX_VECTOR)))
// void USCI0RX_ISR(void)
// {

// }
