/*
 * File: msp430_cli.c
 * Description:
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include "msp_print.h"

/**
 *  Macro definition
 */
#define COMMAND_TBL_LEN sizeof(command_tbl)/sizeof(*(command_tbl))
#define COMMAND_STRING_LEN 256

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
extern unsigned char* parameterString;
extern uint8_t parameterLength;

/**
 *  Private prototype functions
 */
static void CLI_GetCommand(unsigned char* cmd);
static void CLI_Help(void);
static void CLI_Hello(void);

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

    memset(parameterString, 0x00, COMMAND_STRING_LEN);
    parameterLength = 0;

    msp_puts("========================================\n");
    msp_puts("===========MSP430G2 LaunchPad===========\n");
    msp_puts("=========Command Line Interface=========\n");
    msp_puts("========================================\n");

    while (1)
    {
        msp_puts("\nMSP430@CLI > ");

        /* The 'validCommandFlag' is true when the user enter an input command from console */
        while (!validCommandFlag)
        {
            cmd = CLI_GetCommand();

            if (cmd[0] = '\0')
            {
                msp_puts("Missing command!\r\n");
            }

            for (cmd_idx = 0; cmd_idx < COMMAND_TBL_LEN; cmd_idx++)
            {
                if (strcmp(cmd, command_tbl[cmd_idx]) == 0)
                {
                    break;
                }
            }

            /* Execute command */
            command_tbl[cmd_idx].Command_Func();

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
        if ((parameterString[cmd_len] = ' ') || (parameterString[cmd_len] = 0x00))
        {
            strncpy(cmd, parameterString, cmd_len - 1);
            break;
        }
    }
}

static void CLI_Help(void)
{
    /* Print all commands and description for usage */
}

static void CLI_Hello(void)
{
    /* Say "Hello, World!"" */
}
