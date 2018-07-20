---
layout: post
title: "Function Calling Convention"
author: "Nhi Pham"
---

> If you understand stack very well then you will understand how memory works in program and if you understand how memory works in program you will understand how function store in program and if you understand how function store in program you will understand how recursive function works and if you understand how recursive function works you will understand how compiler works and if you understand how compiler works your mind will works as compiler and you will debug any program very easily.

## Fixed argument lists

Function arguments are allocated left to right. They are assigned from r15 to r12. If more parameters are passed than will fit in the registers, the rest are passed on the stack. This should be avoided since the code takes a performance hit when using variables residing on the stack.

## Variable argument lists

Parameters passed to functions that have a variable argument list (printf, scanf, etc.) are all passed on the stack. Any char parameters are extended to ints.

## Return values

The various functions types return the results as follows:

  * char, int and pointer functions return their values r15

  * long and float functions return their values in r15:r14

  * long long functions return their values r15:r14:r13:r12

If the returned value wider than 64 bits, it is returned in memory. The first 'hidden' argument to such a function call will be a memory address. All other arguments will be allocated in the usual way, from r14.

## Reference

* [wikipedia.org - Call_stack](https://en.wikipedia.org/wiki/Call_stack)
* [Journey to the Stack](http://cryptroix.com/2016/10/16/journey-to-the-stack/)
* [Understanding Multiple Recursion](http://cryptroix.com/2016/10/10/understanding-multiple-recursion/)