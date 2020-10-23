obj-m := heal.o
CC = gcc -w
KDIR := /lib/modules/`uname -r`/build
RUBY := /usr/local/bin/ruby

.PHONY: config

all:
	$(MAKE) -C $(KDIR) M=`pwd` modules
clean:
	$(MAKE) -C $(KDIR) M=`pwd` clean
config:
	@ $(RUBY) heal.rb
