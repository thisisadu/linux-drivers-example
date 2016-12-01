KERNELRELEASE	?= `uname -r`
KERNEL_DIR	?= /lib/modules/$(KERNELRELEASE)/build
PWD		:= $(shell pwd)
obj-m		:= jiffies.o
obj-m		+= timer.o

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
