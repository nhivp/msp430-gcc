/*
 * File: drv.h
 * Description: Common type definition for drivers
 *
 * Created by nhivp on 23/07/2018.
 * Copyright (C) 2018 nhivp. All rights reserved.
 */
#ifndef __DRV_H__
#define __DRV_H__
/*****************************************************************************
 * Includes <Header Files>
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "msp430g2553.h"

#define NDEBUG
#ifndef NDEBUG

/*****************************************************************************
* This function is used to check the paramters.
 *****************************************************************************/
#define assert_param(Expression)                   \
{                                                  \
    if (Expression) {                              \
        return 1;                                  \
    } else {                                       \
        return 0;                                  \
    }                                              \
}

#else
#define assert_param(Expression)
#endif /* NDEBUG */


#endif /* __DRV_H__ */