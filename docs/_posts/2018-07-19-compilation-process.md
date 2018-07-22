---
layout: post
title: "Compilation process of a msp430g2553 project"
author: "Nhi Pham"
---

Understanding the compilation process is helpful for us to analyze and detect the problem with ease in compilation process.

The compilation process is the important things for a beginner in microcontroller programming. Some people don't understand it with clarify, that results in they can't fix a problem from the compiling time.

![Compilation process](https://raw.githubusercontent.com/nhivp/msp430-gcc/master/docs/assets/img/compilation_process.png "Compilation process")

The above figure illustrate the compilation process of a simple blinky program.

```
.
├── blink.c
├── drv_gpio.c
└── drv_gpio.h
```

The following is the blink.c program:

```c
#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        /* Stop watchdog timer */
    P1DIR |= 0x40;                   /* Set P1.6 to output direction */

    for(;;)
    {
        P1OUT ^= 0x40;                /* Toggle P1.6 using exclusive-OR */

        /* Wait for 200000 cycles */
        __delay_cycles(200000);
    }
}
```

To compile the program, the compiler will prefrom the preprocessor stage by command ```msp430-gcc -E blink.c -o blink.i``` (The compiling options for the target are ignored, you only focus on the main command for the compilation process).

```shell
nhivp@nhipham:~/mcu/msp430-gcc/demo/blinky/src$ msp430-gcc -E blink.c -o blink.i
nhivp@nhipham:~/mcu/msp430-gcc/demo/blinky/src$ ll
total 24
drwxrwxr-x 2 nhivp nhivp 4096 Th07 22 16:59 ./
drwxrwxr-x 4 nhivp nhivp 4096 Th07 22 15:24 ../
-rw-rw-r-- 1 nhivp nhivp  596 Th07 19 21:37 blink.c
-rw-rw-r-- 1 nhivp nhivp 8719 Th07 22 16:59 blink.i
```

The output is in the form of preprocessed source code, which is sent to the standard output. The following is the output of preprocessor stage.

<details>
<summary> Click to expand </summary>

    # 1 "blink.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 1 "blink.c"

    # 1 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 1 3
    # 58 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    # 1 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/iomacros.h" 1 3
    # 59 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 2 3
    # 112 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    # 1 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/in430.h" 1 3



    # 1 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/intrinsics.h" 1 3
    # 47 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/intrinsics.h" 3
    void __nop (void);

    void __dint (void);

    void __eint (void);

    unsigned int __read_status_register (void);

    typedef unsigned int __istate_t;

    __istate_t __get_interrupt_state (void);

    void __write_status_register (unsigned int sr);

    void __set_interrupt_state (__istate_t sv);

    void *__read_stack_pointer (void);

    void __write_stack_pointer (void *sp);

    void __bic_status_register (unsigned int bits);

    void __bis_status_register (unsigned int bits);

    void __bic_status_register_on_exit (unsigned int bits);

    void __bis_status_register_on_exit (unsigned int bits);

    void *__builtin_frame_address (unsigned int level);


    void *__builtin_return_address (unsigned int level);



    void __delay_cycles (unsigned long int delay);

    unsigned int __swap_bytes (unsigned int v);

    unsigned int __get_watchdog_clear_value ();

    void __set_watchdog_clear_value (unsigned int v);

    void __watchdog_clear ();
    # 5 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/in430.h" 2 3
    # 113 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 2 3
    # 135 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned char IE1 __asm__("__" "IE1");

    extern volatile unsigned char IFG1 __asm__("__" "IFG1");

    extern volatile unsigned char IE2 __asm__("__" "IE2");

    extern volatile unsigned char IFG2 __asm__("__" "IFG2");
    # 172 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned char ADC10DTC0 __asm__("__" "ADC10DTC0");

    extern volatile unsigned char ADC10DTC1 __asm__("__" "ADC10DTC1");

    extern volatile unsigned char ADC10AE0 __asm__("__" "ADC10AE0");

    extern volatile unsigned int ADC10CTL0 __asm__("__" "ADC10CTL0");

    extern volatile unsigned int ADC10CTL1 __asm__("__" "ADC10CTL1");

    extern volatile unsigned int ADC10MEM __asm__("__" "ADC10MEM");

    extern volatile unsigned int ADC10SA __asm__("__" "ADC10SA");
    # 290 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned char DCOCTL __asm__("__" "DCOCTL");

    extern volatile unsigned char BCSCTL1 __asm__("__" "BCSCTL1");

    extern volatile unsigned char BCSCTL2 __asm__("__" "BCSCTL2");

    extern volatile unsigned char BCSCTL3 __asm__("__" "BCSCTL3");
    # 374 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned char CACTL1 __asm__("__" "CACTL1");

    extern volatile unsigned char CACTL2 __asm__("__" "CACTL2");

    extern volatile unsigned char CAPD __asm__("__" "CAPD");
    # 418 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned int FCTL1 __asm__("__" "FCTL1");

    extern volatile unsigned int FCTL2 __asm__("__" "FCTL2");

    extern volatile unsigned int FCTL3 __asm__("__" "FCTL3");
    # 470 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern const volatile unsigned char P1IN __asm__("__" "P1IN");

    extern volatile unsigned char P1OUT __asm__("__" "P1OUT");

    extern volatile unsigned char P1DIR __asm__("__" "P1DIR");

    extern volatile unsigned char P1IFG __asm__("__" "P1IFG");

    extern volatile unsigned char P1IES __asm__("__" "P1IES");

    extern volatile unsigned char P1IE __asm__("__" "P1IE");

    extern volatile unsigned char P1SEL __asm__("__" "P1SEL");

    extern volatile unsigned char P1SEL2 __asm__("__" "P1SEL2");

    extern volatile unsigned char P1REN __asm__("__" "P1REN");

    extern const volatile unsigned char P2IN __asm__("__" "P2IN");

    extern volatile unsigned char P2OUT __asm__("__" "P2OUT");

    extern volatile unsigned char P2DIR __asm__("__" "P2DIR");

    extern volatile unsigned char P2IFG __asm__("__" "P2IFG");

    extern volatile unsigned char P2IES __asm__("__" "P2IES");

    extern volatile unsigned char P2IE __asm__("__" "P2IE");

    extern volatile unsigned char P2SEL __asm__("__" "P2SEL");

    extern volatile unsigned char P2SEL2 __asm__("__" "P2SEL2");

    extern volatile unsigned char P2REN __asm__("__" "P2REN");

    extern const volatile unsigned char P3IN __asm__("__" "P3IN");

    extern volatile unsigned char P3OUT __asm__("__" "P3OUT");

    extern volatile unsigned char P3DIR __asm__("__" "P3DIR");

    extern volatile unsigned char P3SEL __asm__("__" "P3SEL");

    extern volatile unsigned char P3SEL2 __asm__("__" "P3SEL2");

    extern volatile unsigned char P3REN __asm__("__" "P3REN");

    extern const volatile unsigned int TA0IV __asm__("__" "TA0IV");

    extern volatile unsigned int TA0CTL __asm__("__" "TA0CTL");

    extern volatile unsigned int TA0CCTL0 __asm__("__" "TA0CCTL0");

    extern volatile unsigned int TA0CCTL1 __asm__("__" "TA0CCTL1");

    extern volatile unsigned int TA0CCTL2 __asm__("__" "TA0CCTL2");

    extern volatile unsigned int TA0R __asm__("__" "TA0R");

    extern volatile unsigned int TA0CCR0 __asm__("__" "TA0CCR0");

    extern volatile unsigned int TA0CCR1 __asm__("__" "TA0CCR1");

    extern volatile unsigned int TA0CCR2 __asm__("__" "TA0CCR2");
    # 653 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern const volatile unsigned int TA1IV __asm__("__" "TA1IV");

    extern volatile unsigned int TA1CTL __asm__("__" "TA1CTL");

    extern volatile unsigned int TA1CCTL0 __asm__("__" "TA1CCTL0");

    extern volatile unsigned int TA1CCTL1 __asm__("__" "TA1CCTL1");

    extern volatile unsigned int TA1CCTL2 __asm__("__" "TA1CCTL2");

    extern volatile unsigned int TA1R __asm__("__" "TA1R");

    extern volatile unsigned int TA1CCR0 __asm__("__" "TA1CCR0");

    extern volatile unsigned int TA1CCR1 __asm__("__" "TA1CCR1");

    extern volatile unsigned int TA1CCR2 __asm__("__" "TA1CCR2");
    # 685 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned char UCA0CTL0 __asm__("__" "UCA0CTL0");

    extern volatile unsigned char UCA0CTL1 __asm__("__" "UCA0CTL1");

    extern volatile unsigned char UCA0BR0 __asm__("__" "UCA0BR0");

    extern volatile unsigned char UCA0BR1 __asm__("__" "UCA0BR1");

    extern volatile unsigned char UCA0MCTL __asm__("__" "UCA0MCTL");

    extern volatile unsigned char UCA0STAT __asm__("__" "UCA0STAT");

    extern const volatile unsigned char UCA0RXBUF __asm__("__" "UCA0RXBUF");

    extern volatile unsigned char UCA0TXBUF __asm__("__" "UCA0TXBUF");

    extern volatile unsigned char UCA0ABCTL __asm__("__" "UCA0ABCTL");

    extern volatile unsigned char UCA0IRTCTL __asm__("__" "UCA0IRTCTL");

    extern volatile unsigned char UCA0IRRCTL __asm__("__" "UCA0IRRCTL");

    extern volatile unsigned char UCB0CTL0 __asm__("__" "UCB0CTL0");

    extern volatile unsigned char UCB0CTL1 __asm__("__" "UCB0CTL1");

    extern volatile unsigned char UCB0BR0 __asm__("__" "UCB0BR0");

    extern volatile unsigned char UCB0BR1 __asm__("__" "UCB0BR1");

    extern volatile unsigned char UCB0I2CIE __asm__("__" "UCB0I2CIE");

    extern volatile unsigned char UCB0STAT __asm__("__" "UCB0STAT");

    extern const volatile unsigned char UCB0RXBUF __asm__("__" "UCB0RXBUF");

    extern volatile unsigned char UCB0TXBUF __asm__("__" "UCB0TXBUF");

    extern volatile unsigned int UCB0I2COA __asm__("__" "UCB0I2COA");

    extern volatile unsigned int UCB0I2CSA __asm__("__" "UCB0I2CSA");
    # 902 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern volatile unsigned int WDTCTL __asm__("__" "WDTCTL");
    # 950 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430g2553.h" 3
    extern const volatile unsigned char CALDCO_16MHZ __asm__("__" "CALDCO_16MHZ");

    extern const volatile unsigned char CALBC1_16MHZ __asm__("__" "CALBC1_16MHZ");

    extern const volatile unsigned char CALDCO_12MHZ __asm__("__" "CALDCO_12MHZ");

    extern const volatile unsigned char CALBC1_12MHZ __asm__("__" "CALBC1_12MHZ");

    extern const volatile unsigned char CALDCO_8MHZ __asm__("__" "CALDCO_8MHZ");

    extern const volatile unsigned char CALBC1_8MHZ __asm__("__" "CALBC1_8MHZ");

    extern const volatile unsigned char CALDCO_1MHZ __asm__("__" "CALDCO_1MHZ");

    extern const volatile unsigned char CALBC1_1MHZ __asm__("__" "CALBC1_1MHZ");
    # 8 "blink.c" 2

    void main(void)
    {
        WDTCTL = (0x5A00) | (0x0080);
        P1DIR |= 0x40;

        for(;;)
        {
            P1OUT ^= 0x40;


            __delay_cycles(200000);
        }
    }
</details>

The preprocessed output file is quite large. There are three things that preprocessor does:

  * It removes all the comments from our program blink.c

  Before:

  ```c
  void main(void)
  {
      WDTCTL = WDTPW | WDTHOLD;        /* Stop watchdog timer */
      P1DIR |= 0x40;                   /* Set P1.6 to output direction */
      for(;;)
      {
          P1OUT ^= 0x40;                /* Toggle P1.6 using exclusive-OR */
          /* Wait for 200000 cycles */
          __delay_cycles(200000);
      }
  }
  ```

  After:

  ```c
  void main(void)
  {
      WDTCTL = (0x5A00) | (0x0080);
      P1DIR |= 0x40;

      for(;;)
      {
          P1OUT ^= 0x40;


          __delay_cycles(200000);
      }
  }
  ```

  * It includes code from header and source file

  You can see the header files (```msp430g2553.h```, ```iomacros.h``` and ```intrinsics.h```) included into the preprocessed file (```blink.i```).

  * It replaces macros (if there are any that are used in the program) with code.

  Before:

  ```c
  ...
  #define IE1_           0x0000    /* Interrupt Enable 1 */
  ...
  WDTCTL = WDTPW | WDTHOLD;        /* Stop watchdog timer */
  ...
  ```

  After the preprocessor stage, the macro ```WDTPW``` is replaced by ```0x5A00```.

  ```c
  ...
  extern volatile unsigned char IE1 __asm__("__" "IE1");
  ...
  WDTCTL = (0x5A00) | (0x0080);
  ...
  ```

The error often occur in this stage will be ```No such file or directory`` when the include header files are not found.

Error doesn't occur in case the header files which consist of some used macros are not included. For example, the blinky program didn't include the header file ```msp430g2553.h```. And below is result:

```c
# 1 "blink.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "blink.c"
# 9 "blink.c"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= 0x40;

    for(;;)
    {
        P1OUT ^= 0x40;


        __delay_cycles(200000);
    }
}
```

After passing the preprocessor stage, the compiler will compile the source code (*.c) into objects file (*.o).

To know compilation process with more source code such as assembly code, library, ... You can read more at [link](http://www.bogotobogo.com/cplusplus/embeddedSystemsProgramming_gnu_toolchain_ARM_cross_compiler.php).