/*
 * File: msp_print.h
 * Description:
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */

#ifndef _MSP_PRINT_H_
#define _MSP_PRINT_H_

/**
 * Include <Header files>
 **/
#include "msp430g2553.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef printf
#undef printf
#define printf msp_printf
#endif

/**
 * Prototype functions
 **/
extern void uart_init(void);
extern void msp_putnum8it(uint8_t dec_num);
extern void msp_putnum16it(uint16_t dec_num);
extern void msp_putc(unsigned char character);
extern void msp_puts(char* s);

#endif /* _MSP_PRINT_H_ */