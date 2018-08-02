TOPDIR	= $(CURDIR)

SRCS    = $(TOPDIR)/*
OBJECTS = pwm_brightness_led.o

SUPPORT_FILE_DIRECTORY += ~/tools/msp430-elf

DEVICE  = msp430g2553
CC      = msp430-elf-gcc
GDB     = msp430-elf-gdb
FLASH   = mspdebug

CFLAGS += -I $(SUPPORT_FILE_DIRECTORY)/include -mmcu=$(DEVICE) -O0 -g
CFLAGS += -L $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts
CFLAGS += -T $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts/msp430g2553.ld
CFLAGS += -Wl,-Map=pwm_brightness_led.map
LFLAGS =

pwm_brightness_led.o: pwm_brightness_led.c
	$(CC) $(CFLAGS) $(<) -o $(@)

upload:
	$(FLASH) rf2500 "prog pwm_brightness_led.o"

clean:
	rm -rf *.o *.out *.elf *.bin *.map

.PHONY: clean upload
