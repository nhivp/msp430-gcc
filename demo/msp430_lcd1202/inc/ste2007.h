/*
 * Created by nhivp on 19/08/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#ifndef _STE_2007_H_
#define _STE_2007_H_
#include <stdint.h>
#include "msp430g2553.h"

/* Signal control */
#define LCD_PIN_TYPE_OUTPUT P2DIR |= BIT0 + BIT1 + BIT2 + BIT3

#define LCD_CS_LOW          P2OUT &= ~BIT1
#define LCD_CS_HIGH         P2OUT |= BIT1

#define LCD_RESET_LOW       P2OUT &= ~BIT0
#define LCD_RESET_HIGH      P2OUT |= BIT0

#define LCD_SDA_HIGH        P2OUT |= BIT2
#define LCD_SDA_LOW         P2OUT &= ~BIT2

#define LCD_CLK_HIGH        P2OUT |= BIT3
#define LCD_CLK_LOW         P2OUT &= ~BIT3

/* D/!C flag */
#define FLAG_CMD        (0x00)
#define FLAG_DATA       (0x01)

/**
 * LIST OF COMMANDs
 */
/* Display mode */
#define CMD_LCD_MODE    (0xA0)  /* Display mode command identifier */

/**
 * Exported global functions
 */
extern void ste_init(void);
extern void ste_write(char dc, char cmd);

#endif /* _STE_2007_H_ */
