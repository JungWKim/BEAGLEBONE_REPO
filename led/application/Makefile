.SUFFIXES = .c .o

CC = gcc
OBJS = ledApp.o
CFLAGS = -DLOOP
TARGET = ledApp

$(TARGET): $(OBJS)
	gcc -o $@ $<

$(OBJS): $(TARGET).c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET)
