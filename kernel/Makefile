obj-m += ylsm.o
ylsm-objs := init.o debug.o hooks.o ksyms.o x86_hw_breakpoint.o x86_utils.o


DIE_CHAIN = $(shell awk '/die_chain/ { print $$1 }' /boot/Syste.map-`uname -r`||echo 0)

EXTRA_CFLAGS = -I$(PWD)/../include -DROOTKIT_DEBUG -DCOMPILE_TIME_DIE_CHAIN=0x$(DIE_CHAIN)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" clean
