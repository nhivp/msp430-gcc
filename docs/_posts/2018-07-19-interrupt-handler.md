---
layout: post
title: "Hardware interrupt handler in MSP430G2553"
author: "Nhi Pham"
---

When using MSP430's free and open-source GCC toolchain, we can define interrupt handlers with ```__attribute__(interrupt(INTERRUPT_NAME_MACRO))```. For example:

```c
__attribute__ ( ( interrupt( TIMER1_A0_VECTOR ) ) )
void TIMER1_A0_ISR( void )
{
    //Toggle P1.0
    P1OUT ^= 0x01;
}
```

But how exactly does this interrupt magical attribute works? How does the compiler know where exactly to place the interrupt handler's entry address inside the memory, defined by the interrupt vector table? Let's dig it up.

## Interrupt Vector Addresses

First of all, let's connect the dots. We know from the MSP430 specification [SLAU208O, 1.3.6 Interrupt Vectors](http://www.ti.com/lit/ug/slau208q/slau208q.pdf) that the interrupt vectors are located in the address range ```0xFFFF``` to ```0xFF80````, each takes 2 bytes, or 16 bits. Each interrupt vector's value is actually a 16-bit memory address that points to somewhere stores the code to be executed when the corresponding interrupt was raised.

For example, for the previous ```TIMER1_A0_VECTOR``` interrupt, it actually corresponds to the TA1CCR0 interrupt flag if you understands the timer module. Thus we can look up the actual interrupt vector address from [SLAS590M, 6.3 Interrupt Vector Addresses, Table 6-1](http://www.ti.com/lit/ds/symlink/msp430f5529.pdf) (assuming we are using MSP430F552X or MSP430F551X family MCUs). It shows us the interrupt vector address of ```TIMER1_A0_VECTOR``` is indeed ```0xFFE2```.

Specifically, it means at the memory address of ```0xFFE2``` on our MCU's flash, stores the 16-bit value of the memory address of the ```TIMER1_A0_ISR``` function, which will be calculated in the linking process by the linker tool. When the timer module raised an interrupt, the MCU will always read in the 16-bit value from ```0xFFE2```, stop and save the current job, and resume the CPU from the address just read in, which transfer the execution to the ```TIMER1_A0_ISR``` function.

Therefore, there have to be some sort of means to tell the linker to store the specific function's (future-calculated) address into a (pre-defined) memory address space. Thus a Linker Script can be used to assist the job.

## Linker Script

A linker script is actually a memory and sections definition file to tell the linker how to map the input sections from the input object files to the output sections of the single output object file. It can also export symbols (with only addresses but no values) to the C programs sources.

When compiling with MSP430 GCC, a linker script is passed to the linker with ```-T``` command line option defined in your Makefile. For example in my case I'm including a linker script with

```shell
msp430-elf-gcc -L $(MSP430_GCC_DIR)/include -T msp430f5529.ld ...
```

So the linker script is called ```msp430f5529.ld``` resides in the path ```$(MSP430_GCC_DIR)/include```. Actually, all these MCU specific linker scripts were shipped with the full version of the MSP430 GCC (msp430-gcc-full-*), or you can download them separately with [msp430-gcc-support-files-*.zip](http://www.ti.com/tool/msp430-gcc-opensource) also listed in the download page.

If you open the linker script file, you can see the full layout of the device memory including all the interrupt vectors inside a code block called ```MEMORY```. So let's find out where it defines ```0xFFEA```:

```linker
MEMORY {
  ...
  VECT50 : ORIGIN = 0xFFE2, LENGTH = 0x0002
  ...
}
```

This line of code simply defines a memory space called ```VECT50```. The number "50" here is just part of a name, like "a", "b", "c" etc. nothing special. What makes it meaningful is the next part. ```ORIGIN = 0xFFE2``` specifies the start of the memory space at ```0xFFE2``` as we expected, and ```LENGTH = 0x0002``` tells the linker this memory space only takes 2 bytes, so that if we put more than that into the space, some errors may occur during linking.

But ```VECT50``` is only a memory space reference, like a C pointer. We have to "assign" something to the memory value to make it meaningful. This is done in the next code block ```SECTIONS```.

```linker
SECTIONS {
  ...
  __interrupt_vector_50 : {
    KEEP (*(__interrupt_vector_50))
    KEEP (*(__interrupt_vector_timer1_a0))
  } > VECT50
  ...
}
```

WOW, it looks terrifyingly complex. Let's break it down. So the ```SECTIONS``` block defines and assigns values to a set of named sections of the output object file. Practically you can use ```msp430-elf-objdump``` to dump the section table of the compiled ELF object file:

```shell
$ msp430-elf-objdump -h output.elf

Sections:
Idx Name                  Size      VMA       LMA       File off  Algn
  0 __interrupt_vector_50 00000002  0000ffe2  0000ffe2  00000572  2**0
                          CONTENTS, ALLOC,    LOAD,     READONLY, CODE
  1 __reset_vector        00000002  0000fffe  0000fffe  00000576  2**0
                          CONTENTS, ALLOC,    LOAD,     READONLY, DATA
...
```

You can see after linking, a section named ```__interrupt_vector_50``` is exported to the output object file. Its Virtual Memory Address (VMA) and Logical Memory Address (LMA) are both ```0xFFE2```. It explained part of what the above linker script code did. The code ```__interrupt_vector_50 : {} > VECT50``` simply declares an output section ```__interrupt_vector_50``` to be stored inside memory space defined by ```VECT50```, which starts at ```0xFFE2``` and has 2 bytes in size.

What makes it confusing is the inner part. We only defined a section called ```__interrupt_vector_50```, but it's yet empty. To put something inside, we have to map some input sections into this output section.

The term "input section" may be confusing. So let me explain it a little bit. When we compile a C project, the compiler can generate object files for every C source file, such as "a.o" for "a.c", and "b.o" for "b.c" etc. In each object file, code and data are separated into a common set of sections, such as ```.data```, ```.bss```, ```.heap```, ```text``` etc. There may also be some compiler defined and even user defined sections in some object files. When we link the intermediate object files, their sections were passed onto the linker as "input sections". The linker uses a set of rules defined by default or through a linker script to map the input sections from their original files to a set of newly defined sections. And the new sections, called "output sections", will be written to the output object file.

So basically, the inner statement ```*(__interrupt_vector_50)``` is a wildcard expression that includes input sections named ```__interrupt_vector_50``` in all the input object files to the enclosing ```__interrupt_vector_50``` output section. Please don't be confused by the naming. The outer ```__interrupt_vector_50``` is the name of the output section, and the inner one is for the input section. The function ```KEEP()``` informs the compiler's optimizer to keep the mapped section data since it's not referenced by any C code and may be otherwise considered redundant and optimized out.

We can see there's one more statement that includes input sections ```__interrupt_vector_timer1_a0``` from all input object files. So basically it works like an alias for input sections ```__interrupt_vector_50``` in application level.

Now we know the linker puts the contents in the ```__interrupt_vector_50``` or ```__interrupt_vector_timer1_a0``` input sections into the output section called __interrupt_vector_50 which resides at the interrupt vector at address ```0xFFE2``` and takes 2 bytes in space. So the next step is to find out what's actually inside the input sections ```__interrupt_vector_50``` or ```__interrupt_vector_timer1_a0```.

## Exploring with ```objdump```

Before we dive deeper into the compiler implementation, let's pause and see what we can get using the ```msp430-elf-objdump``` utility. First let's see what's actually inside the interrupt vector address ```0xFFE2```.

```shell
$ msp430-elf-objdump -s --start-address=0xFFE2 --stop-address=0xFFE4 output.elf

Contents of section __interrupt_vector_50:
 ffe2 fe46                                 .F
```

We can see that at ```0xFFE2``` there stores a 16-bit value ```0xFE46```. As we already know, it's the memory address of the ```TIMER1_A0_ISR``` interrupt handler function. Since MSP430 processors are little-endian, the actual address should be ```0x46FE```. Now let's see what's inside that address.

As we expected, it leads us to the interrupt handler function. But if you can recall, the value stored in ```0xFFE2``` is actually the contents of input sections ```__interrupt_vector_50``` or ```__interrupt_vector_timer1_a0```. In this case, it means the value of this input section is indeed ```0x46FE```, and is the memory address of the ```TIMER1_A0_ISR``` interrupt handler function.

As I mentioned before, the address of a specific function can only be calculated in the linking process, so it's impossible to hard-code it inside C code, nor in linker scripts. So the only way to put the function address into the memory section's content is through the magical interrupt function attribute implemented in the MSP430 GCC. To understand it, we have to look inside the MSP430 GCC source code. After some quick digging, I found the implementation in ```gcc/gcc/config/msp430/msp430.c```:

```c
void msp430_start_function ( FILE *file, const char *name, tree decl )
{
    tree int_attr;

    int_attr = lookup_attribute ( "interrupt", DECL_ATTRIBUTES ( decl ) );
    if ( int_attr != NULL_TREE )
    {
            tree intr_vector = TREE_VALUE ( int_attr );

            if ( intr_vector != NULL_TREE )
            {
                char buf[101];

                intr_vector = TREE_VALUE ( intr_vector );

                /* The interrupt attribute has a vector value.  Turn this into a
                section name, switch to that section and put the address of
                the current function into that vector slot.  Note msp430_attr()
                has already verified the vector name for us.  */
                if ( TREE_CODE ( intr_vector ) == STRING_CST )
                    sprintf ( buf, "__interrupt_vector_%.80s",
                        TREE_STRING_POINTER ( intr_vector ) );
                else /* TREE_CODE (intr_vector) == INTEGER_CST */
                    sprintf ( buf, "__interrupt_vector_%u",
                        ( unsigned int ) TREE_INT_CST_LOW ( intr_vector ) );

                switch_to_section ( get_section ( buf, SECTION_CODE, decl ) );
                fputs ( "\t.word\t", file );
                assemble_name ( file, name );
                fputc ( '\n', file );
                fputc ( '\t', file );
            }
    }

    switch_to_section ( function_section ( decl ) );
    ASM_OUTPUT_TYPE_DIRECTIVE( file, name, "function" );
    ASM_OUTPUT_FUNCTION_LABEL ( file, name, decl );
}
```

As the comment above suggests, the interrupt attribute takes the interrupt name as its argument. In our example, ```__attribute__ ( ( interrupt( TIMER1_A0_VECTOR ) ) )``` takes ```TIMER1_A0_VECTOR``` as the interrupt name. It's actually a macro defined in the MSP430 driver library:

```c
#define TIMER1_A0_VECTOR   (50)   /* 0xFFE2 Timer1_A3 CC0 */
```

Then the interrupt attribute will create a section with the name prefixing ```__interrupt_vector_``` to the interrupt name. So in our example, the created section is called ```__interrupt_vector_50```. As you may recall, this is indeed the input section name we were expecting to pass onto the linker. Finally the interrupt attribute puts the address of the current annotating function, i.e. ```0x64FE``` for ```TIMER1_A0_ISR``` in our case, into the newly created section.

## Summary

Now we've connected all the dots. Let's wrap it up. Firstly we use ```__attribute__(interrupt(INTERRUPT_NAME_MACRO))``` to tell the compile generate a new section named ```__interrupt_vector_INTERRUPT_NAME_MACRO```, storing the memory address of the annotating interrupt handler function. Then during the linking process, we use the TI provided linker script to map all the interrupt generated sections into correct memory spaces in the interrupt vector table defined by the MSP430 specifications.