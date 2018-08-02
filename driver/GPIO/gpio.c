/*
 * File: gpio.c
 * Description: Implementation of GPIO Driver
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */
/*****************************************************************************
 * Includes <Header Files>
 *****************************************************************************/
#include "gpio.h"

/*****************************************************************************
 * Macro definitions
 *****************************************************************************/

/*****************************************************************************
 * Private typedef definitions
 *****************************************************************************/
typedef struct
{
    volatile unsigned char DIR;
    volatile unsigned char IN;
    volatile unsigned char OUT;
    volatile unsigned char REN;
    volatile unsigned char SEL;
    volatile unsigned char SEL2;
    volatile unsigned char IES;
    volatile unsigned char IE;
    volatile unsigned char IFG;
    GPIO_Callback_t GPIO_Callback_Func[8];
} GPIO_Management_t;

/*****************************************************************************
 * Private global variables
 *****************************************************************************/
static GPIO_Management_t GPIO_Mng_Tbl[]
{
    {P1DIR, P1IN, P1OUT, P1REN, P1SEL, P1SEL2, P1IES, P1IE, P1IFG, {0, 0, 0, 0, 0, 0, 0, 0}}, /* Port 1 */
    {P2DIR, P2IN, P2OUT, P2REN, P2SEL, P2SEL2, P2IES, P2IE, P2IFG, {0, 0, 0, 0, 0, 0, 0, 0}}  /* Port 2 */
};

/*****************************************************************************
 * Private global functions
 *****************************************************************************/

/*****************************************************************************
 * Public global functions
 *****************************************************************************/
void GPIO_Initialize(GPIO_Pin_t aPin, GPIO_Direction_t aDir)
{
    GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].DIR |= (aDir << (aPin % GPIO_PIN_NUM));
}

void GPIO_ConfigInterrupt(GPIO_Pin_t aPin, GPIO_Edge_t aEdge, GPIO_Callback_t aCallBackFunc)
{
    GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].GPIO_Callback_Func[aPin % GPIO_PIN_NUM] = aCallBackFunc;
    GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].IES |= (aEdge << (aPin % GPIO_PIN_NUM));
}

bool GPIO_ReadPin(GPIO_Pin_t aPin)
{
    return (GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].OUT & (aPin % GPIO_PIN_NUM) > 0);
}

uint8_t GPIO_ReadPort(GPIO_Pin_t aPin)
{
    return GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].OUT;
}

void GPIO_WritePin(GPIO_Pin_t aPin, bool aValue)
{
    if (aValue)
    {
        GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].IN |= (1 << (aPin % GPIO_PIN_NUM));
    }
    else
    {
        GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].IN |= (0 << (aPin % GPIO_PIN_NUM));
    }
}

void GPIO_WritePort(GPIO_Pin_t aPin, uint8_t aValue)
{
    GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].IN |= aValue;
}

void GPIO_SelectFunc(GPIO_Pin_t aPin, GPIO_FunctionSel_t aFuncSel)
{
    switch (aFuncSel)
    {
        case GPIO_IO_FUNC:
            GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].SEL  |= (0 << (aPin % GPIO_PIN_NUM));
            GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].SEL2 |= (0 << (aPin % GPIO_PIN_NUM));
            break;

        case GPIO_PRIMARY_FUNC:
            GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].SEL  |= (1 << (aPin % GPIO_PIN_NUM));
            GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].SEL2 |= (0 << (aPin % GPIO_PIN_NUM));
            break;

        case GPIO_SECONDARY_FUNC:
            GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].SEL  |= (1 << (aPin % GPIO_PIN_NUM));
            GPIO_Mng_Tbl[aPin / GPIO_PIN_NUM].SEL2 |= (0 << (aPin % GPIO_PIN_NUM));
            break;

        default:
            /* Error handler */
            break;
    }
}

/*****************************************************************************
 * End of File.
 *****************************************************************************/