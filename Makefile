.PHONY: all
all:
	make -C advanced_linux_programming/chapter01
	make -C advanced_linux_programming/chapter02
	make -C advanced_linux_programming/chapter03
	make -C advanced_linux_programming/chapter04
	make -C advanced_linux_programming/chapter05
	make -C advanced_linux_programming/chapter06
	make -C advanced_linux_programming/chapter07
	make -C advanced_linux_programming/chapter08
	make -C advanced_linux_programming/chapter09
	make -C advanced_linux_programming/chapter10
	make -C linux_sys_prog
	make -C pthread

.PHONY: clean
clean:
	make -C advanced_linux_programming/chapter01 clean
	make -C advanced_linux_programming/chapter02 clean
	make -C advanced_linux_programming/chapter03 clean
	make -C advanced_linux_programming/chapter04 clean
	make -C advanced_linux_programming/chapter05 clean
	make -C advanced_linux_programming/chapter06 clean
	make -C advanced_linux_programming/chapter07 clean
	make -C advanced_linux_programming/chapter08 clean
	make -C advanced_linux_programming/chapter09 clean
	make -C advanced_linux_programming/chapter10 clean
	make -C linux_sys_prog clean
	make -C pthread clean
