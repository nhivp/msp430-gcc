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
    unsigned char Command[32];
    CLI_Command_Function_t Command_Func;
} CLI_Command_t;

/**
 *  Private prototype functions
 */
static void CLI_GetCommand(unsigned char* cmd);
static void CLI_Help(void);
static void CLI_Hello(void);

/**
 *  Private variables
 */
static CLI_Command_t command_tbl[] =
{
    /* Command, Command_Func */
    { "help"  , CLI_Help       },
    { "hi"    , CLI_Hello      }
};

/**
 *  Exported variables
 */
extern unsigned char parameterString[COMMAND_STRING_LEN];
extern uint8_t parameterLength;
extern volatile bool validCommandFlag;


/**
 *  Main Application
 */
int main(void)
{
    unsigned char* cmd;
    uint8_t cmd_idx;

    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    /* Load calibrated DCO vlues to set CPU clock to 1MHz */
    BCSCTL1 = CALBC1_1MHZ;    // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;     // Set DCO to 1MHz
    uart_init();

    msp_puts("\r\n");
    msp_puts("*----------------------------------------*\r\n");
    msp_puts("*           MSP430G2 LaunchPad           *\r\n");
    msp_puts("*         Command Line Interface         *\r\n");
    msp_puts("*----------------------------------------*\r\n");

    msp_puts("\nMSP430@CLI > ");

    __bis_SR_register(GIE); // Enable interrupt

    while (1)
    {

        /* The 'validCommandFlag' is true when the user enter an input command from console */
        while (validCommandFlag)
        {
            msp_puts("\r\nOK");
            // CLI_GetCommand(cmd);

            if (cmd[0] == '\0')
            {
                msp_puts("Missing command!\r\n");
                break;
            }

            msp_puts("\r\nOK");

            for (cmd_idx = 0; cmd_idx < COMMAND_TBL_LEN; cmd_idx++)
            {
                if (strcmp(cmd, command_tbl[cmd_idx].Command) == 0)
                {
                    break;
                }
            }

            /* Execute command */
            command_tbl[cmd_idx].Command_Func();

            msp_puts("\r\nMSP430@CLI > ");

            /* Reset receive buffer and flag*/
            validCommandFlag = false;
            memset(parameterString, 0x00, parameterLength);
            parameterLength = 0;
        }
    }
}

static void CLI_GetCommand(unsigned char* cmd)
{
    uint8_t cmd_len;

    for (cmd_len = 0; cmd_len < parameterLength; cmd_len++)
    {
        if ((parameterString[cmd_len] == ' ') || (parameterString[cmd_len] == 0x00))
        {
            // strncpy(cmd, parameterString, cmd_len - 1);
            break;
        }
        else
        {
            *(cmd++) = parameterString[cmd_len];
        }
    }
}

static void CLI_Help(void)
{
    /* Print all commands and description for usage */
    msp_puts( "Help:\r\n"
              "Please input command as following:\r\n"
    );
}

static void CLI_Hello(void)
{
    /* Say "Hello, World!"" */
}
