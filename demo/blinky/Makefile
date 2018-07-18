TOPDIR	= $(CURDIR)

SRCS    = $(TOPDIR)/src/*
OBJECTS = blink.o

SUPPORT_FILE_DIRECTORY += ~/tools/msp430-elf

DEVICE  = msp430g2553
CC      = msp430-elf-gcc
GDB     = msp430-elf-gdb
OUTPUT	= blink.axf

CFLAGS += -I $(SUPPORT_FILE_DIRECTORY)/include -mmcu=$(DEVICE) -O2 -g
CFLAGS += -L $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts
CFLAGS += -T $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts/msp430g2553.ld
LFLAGS =

blink.o: src/blink.c
	$(CC) $(CFLAGS) $(<) -o $(@)

