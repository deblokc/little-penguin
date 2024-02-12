ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m  := main.o

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

clean:
	rm -rf test
	$(MAKE) -C $(KDIR) M=$$PWD clean

.PHONY: test
test:
	gcc test.c -o test
	./test

endif
