TOPDIR	= $(CURDIR)

SRCS    = $(TOPDIR)/*
OBJECTS = blink.o

SUPPORT_FILE_DIRECTORY += ~/tools/msp430-elf

DEVICE  = msp430g2553
CC      = msp430-elf-gcc
GDB     = msp430-elf-gdb
FLASH   = mspdebug
OUTPUT	= blink.axf

CFLAGS += -I $(SUPPORT_FILE_DIRECTORY)/include -mmcu=$(DEVICE) -O0 -g
CFLAGS += -L $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts
CFLAGS += -T $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts/msp430g2553.ld
CFLAGS += -Wl,-Map=blink.map
LFLAGS =

blink.o: blink.c
	$(CC) $(CFLAGS) $(<) -o $(@)

upload:
	$(FLASH) rf2500 "prog blink.o"

clean:
	rm -rf *.o *.out *.elf *.bin *.map

.PHONY: clean upload
