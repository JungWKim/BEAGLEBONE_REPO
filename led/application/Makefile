.SUFFIXES = .c .o

CC = gcc
OBJS = ledApp.o
CFLAGS = -g
TARGET = ledApp

$(TARGET): $(OBJS)
	gcc -o $@ $<

$(OBJS): $(TARGET).c
	gcc -c -o $@ $<

clean:
	rm -rf $(OBJS) $(TARGET)
