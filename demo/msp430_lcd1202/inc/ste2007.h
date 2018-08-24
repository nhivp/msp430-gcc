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
#define LCD_CONTRAST                (0x9F)      // Value range should be 0x80 -> 0x9F

#define FLAG_CMD                    (0x00)
#define FLAG_DATA                   (0x01)

// Display mode
#define ON                          (0x0F)  // Display on
#define OFF                         (0x0E)  // Display off
#define ALL                         (0x05)  // All points ON
#define NORMAL                      (0x04)  // Normal display
#define NON_REVERSE                 (0x06)  // Non-reverse display
#define REVERSE                     (0x07)  // Reverse display

#define LCD_MODE                    (0xA0)  // Display mode command identifier

#define LCD_NOP                     (0xE3)
#define LCD_CHARGE_PUMP_ON          (0x2F)
#define LCD_RAM_ADDR_VER_MODE       (0xAB)
#define LCD_RAM_ADDR_HOR_MODE       (0xAA)
#define LCD_CHANGE_COL_LSB          (0x00)
#define LCD_CHANGE_COL_MSB          (0x10)
#define LCD_CHANGE_ROW              (0xB0)
#define LCD_MIRROR_Y                (0xC8)
#define LCD_MIRROR_X                (0xA1)
#define LCD_EXT_OSC                 (0x3A)
#define LCD_SOFT_RESET              (0xE2)


/**
 * Exported global functions
 */
extern void ste_init(void);
extern void ste_write(char dc, char cmd);

#endif /* _STE_2007_H_ */
