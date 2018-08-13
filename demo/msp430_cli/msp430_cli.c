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
    /* Command, Command_Func */
    { "help"  , CLI_Help       },
    { "info"  , CLI_Info       },
    { "hello" , CLI_Hello      }
};

/**
 *  Exported variables
 */
extern char parameterString[COMMAND_STRING_LEN];
extern uint8_t parameterLength;
extern volatile bool validCommandFlag;


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
             CLI_GetCommand(cmd);

            if (cmd[0] == '\0')
            {
                msp_puts("Missing command!\r\n");
                validCommandFlag = false;
                break;
            }

            for (cmd_idx = COMMAND_LEN(command_tbl) - 1; cmd_idx > 0; cmd_idx--)
            {
                if (!strcmp((char*)cmd, (char*)command_tbl[cmd_idx].Command))
                {
                    break;
                }
            }

            /* Execute command */
            command_tbl[cmd_idx].Command_Func();

            msp_puts("\r\nMSP430@CLI > ");

            /* Reset receive buffer and flag*/
            memset(parameterString, '\0', parameterLength + 1);
            memset(cmd, '\0', 32);
            parameterLength = 0;
            validCommandFlag = false;
        }
    }
}

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
    msp_puts("Hello, World!\r\n");
}

static void CLI_Info(void)
{
    msp_puts("\r\nDevice Info:");
}
