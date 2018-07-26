TOPDIR	= $(CURDIR)

SRCS    := $(wildcard *.c)
OBJECTS := $(SRCS:.c=.o)
DEPS    := $(SRCS:.c=.d)
TARGET  := serial_console.out

SUPPORT_FILE_DIRECTORY += ~/tools/msp430-elf

DEVICE  = msp430g2553
CC      = msp430-elf-gcc
LD      = msp430-elf-ld
GDB     = msp430-elf-gdb
FLASH   = mspdebug

CFLAGS += -I $(SUPPORT_FILE_DIRECTORY)/include -mmcu=$(DEVICE) -O0 -g
CFLAGS += -L $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts
CFLAGS += -I $(TOPDIR)
LFLAGS += -L $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts
LFLAGS += -T $(SUPPORT_FILE_DIRECTORY)/lib/ldscripts/msp430g2553.ld
LFLAGS += -I $(SUPPORT_FILE_DIRECTORY)/include
# LFLAGS += -L /home/nhivp/tools/msp430-elf/lib/gcc/msp430-elf/7.3.1/430
# LFLAGS += -lgcc
# LFLAGS += -Wl,-Map=serial_console.map

all: $(TARGET)
	@echo $(SRCS)
	@echo $(OBJECTS)
	@echo $(DEPS)

$(TARGET): $(OBJECTS)
	$(LD) -mmcu=msp430g2553 $(LFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MD -MF $(subst .c,.d,$<) $< -c -o $@

upload:
	$(FLASH) rf2500 "prog serial_console.elf"

clean:
	rm -rf *.o *.out *.elf *.bin *.map *.d

.PHONY: clean upload
