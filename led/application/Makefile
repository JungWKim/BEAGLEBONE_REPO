.SUFFIXES = .c .o
CC = gcc
CFLAGS = -g
TARGET = ledApp

$(TARGET): $(TARGET).o
	gcc -o $@ $<

$(TARGET).o: $(TARGET).c
	gcc -c -o $@ $<
