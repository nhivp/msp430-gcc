TOPDIR	= ../

SRCS    = $(TOPDIR)/src/*
OBJECTS = blink.o

GCC_DIR =  /opt/ti/gcc/bin
SUPPORT_FILE_DIRECTORY = $(TOPDIR)/inc

DEVICE  = msp430g2553
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb
OUTPUT	= DemoApp.axf

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)

build: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $(SRCS) -o $(OUTPUT)

