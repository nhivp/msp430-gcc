---
layout: post
title: "Linker Scripts for MSP430G2553"
author: "Nhi Pham"
---

This post will expain some words used in linker scripts of msp430g2553.
The following is an illustration of linking operation:

![Linker Script](https://raw.githubusercontent.com/nhivp/msp430-gcc/master/docs/assets/img/linker_script.png "An illustration of linking operation")

First of all, we will dissect the first line in the linker script.

```Makefile
ENTRY(_start)
```

This defines the entry point into the chip. On exit from a reset condition, the first thing that the MCU executes is at ```_start```. To view this section (```_start```) please find in the linker script.

The linker script then defines the sections of the memory map that in to which it will map the various sections of the object files. It does this in ```Memory``` section.

```Makefile
MEMORY {
  SFR              : ORIGIN = 0x0000, LENGTH = 0x0010 /* END=0x0010, size 16 */
  RAM              : ORIGIN = 0x0200, LENGTH = 0x0200 /* END=0x03FF, size 512 */
  INFOMEM          : ORIGIN = 0x1000, LENGTH = 0x0100 /* END=0x10FF, size 256 as 4 64-byte segments */
  INFOA            : ORIGIN = 0x10C0, LENGTH = 0x0040 /* END=0x10FF, size 64 */
  INFOB            : ORIGIN = 0x1080, LENGTH = 0x0040 /* END=0x10BF, size 64 */
  INFOC            : ORIGIN = 0x1040, LENGTH = 0x0040 /* END=0x107F, size 64 */
  INFOD            : ORIGIN = 0x1000, LENGTH = 0x0040 /* END=0x103F, size 64 */
  ROM (rx)         : ORIGIN = 0xC000, LENGTH = 0x3FDE /* END=0xFFDD, size 16350 */
  BSLSIGNATURE     : ORIGIN = 0xFFDE, LENGTH = 0x0002
  VECT1            : ORIGIN = 0xFFE0, LENGTH = 0x0002
  VECT2            : ORIGIN = 0xFFE2, LENGTH = 0x0002
  VECT3            : ORIGIN = 0xFFE4, LENGTH = 0x0002
  VECT4            : ORIGIN = 0xFFE6, LENGTH = 0x0002
  VECT5            : ORIGIN = 0xFFE8, LENGTH = 0x0002
  VECT6            : ORIGIN = 0xFFEA, LENGTH = 0x0002
  VECT7            : ORIGIN = 0xFFEC, LENGTH = 0x0002
  VECT8            : ORIGIN = 0xFFEE, LENGTH = 0x0002
  VECT9            : ORIGIN = 0xFFF0, LENGTH = 0x0002
  VECT10           : ORIGIN = 0xFFF2, LENGTH = 0x0002
  VECT11           : ORIGIN = 0xFFF4, LENGTH = 0x0002
  VECT12           : ORIGIN = 0xFFF6, LENGTH = 0x0002
  VECT13           : ORIGIN = 0xFFF8, LENGTH = 0x0002
  VECT14           : ORIGIN = 0xFFFA, LENGTH = 0x0002
  VECT15           : ORIGIN = 0xFFFC, LENGTH = 0x0002
  RESETVEC         : ORIGIN = 0xFFFE, LENGTH = 0x0002
}
```

It shows that the Flash memory (```ROM```) section starts at address ```0xC000``` and is ```15KB``` long or ```15,360 bytes``` long which in hex is ```0x3FDE```. The RAM memory section starts a address ```0x20000000``` and is ```8KB``` long or ```8192 bytes``` long, which in hex is ```0x02000``` . All of this information is provided to the linker via the memory section of the linker script. Also note the the ```ROM``` memory s defined as (rx) which means that it has read and execute only, whereas the ```RAM``` memory is defined as (xrw) which means that it is read, write and execute.

The next major section of the linker script is called ```SECTIONS```. It defines where each if the various sections of the object files goes into the memory map defined in the ```MEMORY``` section.

```Makefile
SECTIONS
{
    .bslsignature       : {} > BSLSIGNATURE
    __interrupt_vector_1   : { KEEP (*(__interrupt_vector_1 )) KEEP (*(__interrupt_vector_trapint)) } > VECT1
    __interrupt_vector_2   : { KEEP (*(__interrupt_vector_2 )) } > VECT2
    __interrupt_vector_3   : { KEEP (*(__interrupt_vector_3 )) KEEP (*(__interrupt_vector_port1)) } > VECT3
    __interrupt_vector_4   : { KEEP (*(__interrupt_vector_4 )) KEEP (*(__interrupt_vector_port2)) } > VECT4
    __interrupt_vector_5   : { KEEP (*(__interrupt_vector_5 )) } > VECT5
    __interrupt_vector_6   : { KEEP (*(__interrupt_vector_6 )) KEEP (*(__interrupt_vector_adc10)) } > VECT6
    __interrupt_vector_7   : { KEEP (*(__interrupt_vector_7 )) KEEP (*(__interrupt_vector_usciab0tx)) } > VECT7
    __interrupt_vector_8   : { KEEP (*(__interrupt_vector_8 )) KEEP (*(__interrupt_vector_usciab0rx)) } > VECT8
    __interrupt_vector_9   : { KEEP (*(__interrupt_vector_9 )) KEEP (*(__interrupt_vector_timer0_a1)) } > VECT9
    __interrupt_vector_10  : { KEEP (*(__interrupt_vector_10)) KEEP (*(__interrupt_vector_timer0_a0)) } > VECT10
    __interrupt_vector_11  : { KEEP (*(__interrupt_vector_11)) KEEP (*(__interrupt_vector_wdt)) } > VECT11
    __interrupt_vector_12  : { KEEP (*(__interrupt_vector_12)) KEEP (*(__interrupt_vector_comparatora)) } > VECT12
    __interrupt_vector_13  : { KEEP (*(__interrupt_vector_13)) KEEP (*(__interrupt_vector_timer1_a1)) } > VECT13
    __interrupt_vector_14  : { KEEP (*(__interrupt_vector_14)) KEEP (*(__interrupt_vector_timer1_a0)) } > VECT14
    __interrupt_vector_15  : { KEEP (*(__interrupt_vector_15)) KEEP (*(__interrupt_vector_nmi)) } > VECT15
    __reset_vector :
    {
        KEEP (*(__interrupt_vector_16))
        KEEP (*(__interrupt_vector_reset))
        KEEP (*(.resetvec))
    } > RESETVEC
.......
```

The first section defined under SECTIONS is the ```__interrupt_vector_{VECTOR_NUMBER}``` section. This section contains the interrupt vector table and reset vector i.e. the body of the interrupt vector 1 routine specified stored at an address ```0xFFE0``` with 2 width bytes (from ```0xFFE0``` to ```0xFFE1```).

```Makefile
......
    .rodata :
    {
        . = ALIGN(2);
        *(.plt)
        *(.rodata .rodata.* .gnu.linkonce.r.* .const .const:*)
        *(.rodata1)
        KEEP (*(.gcc_except_table)) *(.gcc_except_table.*)
        PROVIDE (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE (__preinit_array_end = .);
        PROVIDE (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE (__init_array_end = .);
        PROVIDE (__fini_array_start = .);
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        PROVIDE (__fini_array_end = .);
    } > ROM
.......
```

The ```ALIGN(2)``` instructions tells the linker that this section ought to be word aligned. Since this is a 16-bit machine it typically needs to be word aligned (16-bit -> 2 bytes hence the '2' specified with the align command. )

## Output Section Description

The full description of an output section looks like this:

```Makefile
section [address] [(type)] : [AT(lma)]
{
    output-section-command
    output-section-command
    ...
} [>region] [AT>lma_region] [:phdr :phdr …] [=fillexp]
```

## Output sections

* ```.text```:
* ```.bss```:
* ```.data```:

## Simple Linker Script Commands

*

## Assigning Values to Symbols

* PROVIDE

* KEEP

## SECTIONS Command


## Reference

* [Linker Command Language](https://sourceware.org/binutils/docs/ld/index.html) - Reference for concept or syntax.
