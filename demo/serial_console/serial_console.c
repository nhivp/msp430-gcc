/***************************************************************************************
  file: serial_console.c
  description: implement a serial console that send the characters to computer terminal
  Nhi Pham @ 2018
***************************************************************************************/

#include <msp430g2553.h>
#include "msp430_printf.h"

void UARTConfigure(void);
void UARTSendChar(unsigned char character);
void UARTSendArray(unsigned char* TxArray, unsigned char ArrayLength);
void UARTSendString(char* TxArray);

volatile unsigned char UARTRxData[20];
volatile unsigned char UARTRxFlag = 0;
volatile char i=0;

/**************************************************
 * Main program.
 **************************************************/
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    /* Load calibrated DCO vlues to set CPU clock to 1MHz */
    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    UARTConfigure();
    printformat("[nhi pham]\r\n");
    UARTSendString("Hello World");
    UARTSendString("\r\n");

    while(1)
    {
        if (UARTRxFlag)
        {
            UARTSendArray(UARTRxData,UARTRxFlag);
            UARTSendString("\r\n");
        }

        __bis_SR_register(CPUOFF+GIE); // Put CPU to sleep in LPM0 with interrupts enabled
    }
}

void UARTConfigure(void)
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

__attribute__ ((alias("UARTSendChar"))) int printf(const char *fmt, ...);

void UARTSendChar(unsigned char character)
{
    // Send a single byte using the hardware UART 0
    // Example usage: UARTSendChar('a');

    while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
    UCA0TXBUF = character; //Write the character at the location specified by the pointer and increment pointer
}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength)
{
    // Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
    // Example usage: UARTSendArray("Hello", 5);
    // int data[2]={1023, 235};
    // UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

    while(ArrayLength--)
    { // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray++; //Write the character at the location specified by the pointer and increment pointer
    }
}

void UARTSendString(char *TxArray)
{
    // Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
    // Example usage: UARTSendArray("Hello", 5);
    // int data[2]={1023, 235};
    // UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

    while(*TxArray)
    {
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray++; //Write the character at the location specified by the pointer and increment pointer
    }
}

/**************************************************
 * USCI0RX_ISR Interrupt Handler
 **************************************************/
__attribute__ ((interrupt(USCIAB0RX_VECTOR)))
void USCI0RX_ISR(void)
{
    UARTRxData[i] = UCA0RXBUF; /* Read USART data register */

    if(UARTRxData[i++]=='\r')
    {
        UARTRxFlag=--i; /* Set String received flag to length of received string */
        i=0;            /* Reset buffer index */
        __bic_SR_register_on_exit(CPUOFF);
    }
}
/*___End of file___ */