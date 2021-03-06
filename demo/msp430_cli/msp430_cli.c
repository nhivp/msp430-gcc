/*
 * File: msp430_cli.c
 * Description:
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include "msp_print.h"
#include <string.h>


/**
 *  Typedef definition
 */
typedef void (*CLI_Command_Function_t)(void);

typedef struct
{
    char Command[32];
    char Command_Desc[64];
    CLI_Command_Function_t Command_Func;
} CLI_Command_t;

/**
 *  Private prototype functions
 */
static void CLI_GetCommand(unsigned char* cmd);
static void CLI_Help(void);
static void CLI_Hello(void);
static void CLI_Info(void);

/**
 *  Private variables
 */
static CLI_Command_t command_tbl[] =
{
    /* Command, Description,                    Command_Func */
    { "help"  , "Show a list of command.",      CLI_Help     },
    { "info"  , "Show all features of MCU",     CLI_Info     },
    { "hello" , "Say Hello, World.",            CLI_Hello    }
};

/**
 *  Exported variables
 */
extern char parameterString[COMMAND_STRING_LEN];
extern uint8_t parameterLength;
extern volatile bool validCommandFlag;
extern volatile uint16_t __m_flash_size;
extern volatile uint16_t __m_ram_size;


/**
 *  Main Application
 */
int main(void)
{
    unsigned char cmd[32];
    uint8_t cmd_idx;

    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    /* Load calibrated DCO vlues to set CPU clock to 1MHz */
    BCSCTL1 = CALBC1_1MHZ;    // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;     // Set DCO to 1MHz
    uart_init();
    memset(parameterString, '\0', COMMAND_STRING_LEN);
    memset(cmd, '\0', 32);

    msp_puts("\r\n");
    msp_puts("*----------------------------------------*\r\n");
    msp_puts("*         MSP-EXP430G2 LaunchPad         *\r\n");
    msp_puts("*         Command Line Interface         *\r\n");
    msp_puts("*----------------------------------------*\r\n");
    msp_puts("\n<< System Info >>\r\n");
    msp_puts("\tMCU:                     MSP430G2553\r\n");
    msp_puts("\tFLASH:                   16kB\r\n");
    msp_puts("\tFLASH used:              ");
    msp_putnum16it(__m_flash_size);
    msp_puts("\r\n");
    msp_puts("\tRAM:                     512B\r\n");
    msp_puts("\tRAM used:                ");
    msp_putnum16it(__m_ram_size);
    msp_puts("\r\n");
    msp_puts("\tSystem clock:            1MHz\r\n");
    msp_puts("\tSystem console baudrate: 9600bps\r\n");
    msp_puts("\r\n\r\nMSP430@CLI > ");

    __bis_SR_register(GIE); /* Enable interrupt */

    while (1)
    {
        /* The 'validCommandFlag' is true when the user enter an input command from console */
        while (validCommandFlag)
        {
            CLI_GetCommand(cmd);

            if (cmd[0] == '\0')
            {
                msp_puts("\r\nMissing command!");
            }
            else
            {
                for (cmd_idx = 0; cmd_idx < COMMAND_LEN(command_tbl); cmd_idx++)
                {
                    if (!strcmp((char*)cmd, (char*)command_tbl[cmd_idx].Command))
                    {
                        break;
                    }
                }

                if (cmd_idx < COMMAND_LEN(command_tbl))
                {
                    /* Execute command */
                    command_tbl[cmd_idx].Command_Func();
                }
                else
                {
                    msp_puts("\r\nInvalid command!");
                }
            }

            msp_puts("\r\nMSP430@CLI > ");

            /* Reset receive buffer and flag*/
            memset(parameterString, '\0', parameterLength + 1);
            memset(cmd, '\0', 32);
            parameterLength = 0;
            validCommandFlag = false;
        }
    }
}

/**
 *  Get a command from the input string.
 */
static void CLI_GetCommand(unsigned char* cmd)
{
    uint8_t cmd_len;

    for (cmd_len = 0; cmd_len < parameterLength; cmd_len++)
    {
        if ((parameterString[cmd_len] == ' ')
                || (parameterString[cmd_len] == '\0')
                || (parameterString[cmd_len] == 0x0D))
        {
            strncpy((char*)cmd, (char*)parameterString, cmd_len);
            break;
        }
    }
}

/**
 * Command executing: help
 */
static void CLI_Help(void)
{
    uint8_t i;
    /* Print all commands and description for usage */
    msp_puts( "\r\n\r\nPlease input command as follows:");

    for (i = 0; i < COMMAND_LEN(command_tbl); i++)
    {
        msp_puts("\r\n\t* ");
        msp_puts(command_tbl[i].Command);
        msp_puts(": ");
        msp_puts(command_tbl[i].Command_Desc);
    }
    msp_puts("\r\n");
}

/**
 * Command executing: hello
 */
static void CLI_Hello(void)
{
    /* Say "Hello, World!"" */
    msp_puts("\r\nHello, World!");
    msp_puts("\r\nI'm Nhi Pham. You'll find me on Earth.");
}

/**
 * Command executing: info
 */
static void CLI_Info(void)
{
    msp_puts("\r\n<< Device Info >>");
    msp_puts("\r\n\tCPU:             msp430g2553 @ 16bit RISC Architecture");
    msp_puts("\r\n\tArchitecture:    16bit RISC Architecture");
    msp_puts("\r\n\tCPU clock:       16MHz");
    msp_puts("\r\n\tFlash:           16kB");
    msp_puts("\r\n\tRAM:             512B");
    msp_puts("\r\n\tI/O:             16 I/O Pins");
    msp_puts("\r\n\tTimer:           Two 16-bit Timer_A");
    msp_puts("\r\n\tADC:             10-bit 200-ksps");
    msp_puts("\r\n\tComunication:    I2C/SPI/UART");
    msp_puts("\r\n\tDebug interface: JTAG + Spy-Bi-wire");
}
