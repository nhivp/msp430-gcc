/******************************************************************************
  file: debug_log.c
  description: Implement a debug log fufnction that it is to print out log.
  Nhi Pham @ 2018
*******************************************************************************/

#include <msp430g2553.h>
#include "debug_log.h"

static void UARTConfigure(void);
static void UARTSendChar(unsigned char c);
static void UARTSendString(const unsigned char *str);
static void convert_num2str(uint16_t num, unsigned char* str);

void debug_init(void)
{
    UARTConfigure();
    // __delay_cycles(1000);
    // UARTSendString("debug_init --> OK\r\n");
    // debug_log("Test = 0x", 45);
}

/* Print a message, plus a hex number
 * E.g. "The value of register: 0x0001"
 */
void debug_log(unsigned char* msg, uint16_t data)
{
    unsigned char data_str[5];
    UARTSendString(msg);
    convert_num2str(data, &data_str[0]);
    UARTSendString(&data_str[0]);
    UARTSendString("\r\n");
}

static void UARTConfigure(void)
{
    /* Configure hardware UART */
    P1SEL = BIT2 ;          // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT2 ;         // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;   // Use SMCLK
    UCA0BR0 = 104;          // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
    UCA0BR1 = 0;            // Set baud rate to 9600 with 1MHz clock
    UCA0MCTL = UCBRS0;      // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;   // Initialize USCI state machine
}

static void UARTSendChar(unsigned char c)
{
    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = c;
}

static void UARTSendString(const unsigned char *str)
{
    while(*str != '\0')
    {
        UARTSendChar(*str);
        str++;
    }
}

static void convert_num2str(uint16_t num, unsigned char* str)
{
    uint16_t temp;
    uint16_t quotient;
    unsigned char hex_temp[4] = {'0', '0', '0', '0'};
    uint8_t hex_len = 0;

    quotient = num;

    while(quotient != 0)
    {
        temp = quotient % 16;
        //To convert a character
        if( temp < 10)
        {
            temp =temp + 48;
        }
        else
        {
            temp = temp + 55;
        }

        quotient = quotient / 16;
        hex_temp[hex_len++] = (unsigned char* )temp;
    }

    *(str++) = hex_temp[3];
    *(str++) = hex_temp[2];
    *(str++) = hex_temp[1];
    *(str++) = hex_temp[0];

    *str = '\0';
}