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

#ifdef printf
#undef printf
#define printf msp_printf
#endif

/**
 * Prototype functions
 **/
extern void uart_init(uint16_t baudrate);
extern void msp_printf(char *format, ...);
extern void msp_putc(unsigned char character);
extern void msp_puts(char* s);

#endif /* _MSP_PRINT_H_ */