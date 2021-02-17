.SUFFIXES = .c .o

CC = gcc
TARGET = led
OBJS = led.o
CFLAGS = -g 

all: $(TARGET).o
	gcc -o $(TARGET) $<

$(TARGET).o: $(TARGET).c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(TARGET) *.o
