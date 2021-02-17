obj-m = led.o
KDIR = /lib/modules/$(shell uname -r)/build

default:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	rm -rf *.o *.mod.* *.ko *.d
