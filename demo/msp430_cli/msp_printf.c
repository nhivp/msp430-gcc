/*
 * File: msp_print.c
 * Description:
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include "msp_print.h"

/**
 *  Exported variables
 */
char parameterString[COMMAND_STRING_LEN];
uint8_t parameterLength;
volatile bool validCommandFlag;


static void puth(unsigned char n);

/**
 * Private variables
 */
static const uint8_t hex_num_tbl[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                        'A', 'B', 'C', 'D', 'E', 'F'};

void uart_init(void)
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
}

static void puth(unsigned char n)
{
    msp_putc(hex_num_tbl[n & 15]);
}

/**
 * Sends a 8-bit (hexa number) out through UART
 */
void msp_putnum8it(uint8_t dec_num)
{
    msp_putc(hex_num_tbl[dec_num & 0xF]);
}

/**
 * Sends a 16-bit (hexa number) out through UART
 */
void msp_putnum16it(uint16_t dec_num)
{
    // uint8_t temp_hex;

    // /* Print the first number */
    // temp_hex = (uint8_t)((dec_num >> 4) & 0xF);
    // msp_putc(hex_num_tbl[temp_hex]);

    // /* Print the sencond number */
    // temp_hex = 0;
    // temp_hex = (uint8_t)(dec_num & 0xF);
    // msp_putc(hex_num_tbl[temp_hex]);

    puth(dec_num >> 12);
    puth(dec_num >> 8);
    puth(dec_num >> 4);
    puth(dec_num);
}

/**
 * Sends a single byte out through UART
 */
void msp_putc(unsigned char character)
{
    while (!(IFG2 & UCA0TXIFG)); // USCI_A0 TX buffer ready?
    UCA0TXBUF = character;       // TX -> RXed character
}

/**
 * Sends a string out through UART
 */
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
__attribute__ ((interrupt(USCIAB0RX_VECTOR)))
void USCI0RX_ISR(void)
{
    parameterString[parameterLength] = UCA0RXBUF;
    msp_putc(parameterString[parameterLength]); /* Echo */

    /* Also get the characters '\r\n' */
    if (parameterString[parameterLength++] == '\r')
    {
        validCommandFlag = true;
    }
}
