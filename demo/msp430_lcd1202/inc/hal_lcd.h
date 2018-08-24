/*
 * Created by nhivp on 19/08/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#ifndef _HAL_LCD_H_
#define _HAL_LCD_H_
#include <stdint.h>

extern void lcd_init(void);
extern void lcd_printc(char c);
extern void lcd_prints(char* s);
extern void lcd_printf(char *format, ...);
extern void lcd_gotoxy(uint8_t col, uint8_t row);
extern void lcd_displayImage(uint8_t row, uint8_t column,
                            uint8_t height, uint8_t width,
                            uint8_t* image);
extern void lcd_home(void);
extern void lcd_clear(void);
extern void lcd_normal(void);

#endif /* _HAL_LCD_H_ */
