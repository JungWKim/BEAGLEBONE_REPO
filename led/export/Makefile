.SUFFIXES: .c .o

CC = gcc 
OBJS = led.o
TARGET = led

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $<
	
led.o: led.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS) $(TARGET)
