TOPDIR	= $(CURDIR)

SRCS    = $(TOPDIR)/*
OBJECTS = serial_console.o

SUPPORT_FILE_DIRECTORY += ~/tools/msp430-elf

DEVICE  = msp430g2553
CC      = msp430-elf-gcc
GDB     = msp430-elf-gdb
FLASH   = mspdebug

CFLAGS += -I $(SUPPORT_FILE_DIRECTORY)/include -mmcu=$(DEVICE) -O0 -g
CFLAGS += -L $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts
CFLAGS += -T $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts/msp430g2553.ld
CFLAGS += -Wl,-Map=serial_console.map
LFLAGS =

serial_console.o: serial_console.c
	$(CC) $(CFLAGS) $(<) -o $(@)

upload:
	$(FLASH) rf2500 "prog serial_console.o"

clean:
	rm -rf *.o *.out *.elf *.bin *.map

.PHONY: clean upload
