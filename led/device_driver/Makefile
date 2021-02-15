obj-m = led.o
KDIR = /usr/include

all:
	make -C /usr/include M=$(shell pwd) modules

clean:
	rm led.o led.mod led.mod.c led.mod.o modules.order Module.symvers led.ko
