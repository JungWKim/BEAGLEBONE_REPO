obj-m = led.o
KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	rm -f *.o *.d *.mod.* *.ko 
