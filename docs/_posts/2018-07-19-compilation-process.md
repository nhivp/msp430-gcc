---
layout: post
title: "Compilation process of a msp430g2553 project"
author: "Nhi Pham"
---

Understanding the compilation process is helpful for us to analyze and detect the problem with ease in compilation process.

The compilation process is the important things for a beginner in microcontroller programming. Some people don't understand clearly it, that results in they can't fix a problem from the compiling time.

![Compilation process](https://raw.githubusercontent.com/nhivp/msp430-gcc/master/docs/assets/img/compilation_process.png "Compilation process")

The above figure illustrate the compilation process of a simple blinky program.

```
.
├── blink.c
├── drv_gpio.c
└── drv_gpio.h
```

To compile the program, the compiler will prefrom the preprocessor step by command ```msp430-gcc -E blink.c``` and ```msp430-gcc -E drv_gpio.c``` (The compiling options for the target are ignored, you only focus on the main command for the compilation process).

To know compilation process with more source code such as assembly code, library, ... You can read more at [link](http://www.bogotobogo.com/cplusplus/embeddedSystemsProgramming_gnu_toolchain_ARM_cross_compiler.php).