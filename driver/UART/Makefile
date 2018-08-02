TARGET	:= $(addprefix ../libs/lib,$(addsuffix .a,$(notdir $(CURDIR))))

SRCS	:= $(wildcard ./*.c)
OBJECTS	:= $(SRC:.c=.o)

#-------------------------------------------------------------------------------
all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(AR) -r $(TARGET) $^

%.o: %.c
	$(CC) $(CFLAGS) -MD -MF $(subst .c,.d,$<) -c -o $@  $<

.PHONY: all
