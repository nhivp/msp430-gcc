/*
 * Created by nhivp on 19/08/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#include "ste2007.h"

void ste_init(void)
{
    LCD_PIN_TYPE_OUTPUT;
    LCD_RESET_LOW;
    LCD_CS_HIGH;
    LCD_CLK_LOW;
    LCD_RESET_HIGH;
}

void ste_write(char dc, char byte)
{
    char i;

    /* shift D/!C out */
    if(dc)
    {
        LCD_SDA_HIGH;
    }
    else
    {
        LCD_SDA_LOW;
    }

    LCD_CS_LOW;
    LCD_CLK_HIGH;
    LCD_CLK_LOW;

    /* shift data out */
    for(i = 0; i < 8; i++)
    {
        if((byte<<i) & 0x80)
        {
            LCD_SDA_HIGH;
        }
        else
        {
            LCD_SDA_LOW;
        }

        LCD_CLK_HIGH;
        LCD_CLK_LOW;
    }
    // __delay_cycles(5);
    LCD_CS_HIGH;
}