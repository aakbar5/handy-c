CC := gcc
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: stat clocks sched_info pid epoll vector_io mmap_io

.PHONY: stat
stat: stat.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clocks
clocks: clocks.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o clocks clocks.c

.PHONY: sched_info
sched_info: sched_info.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: pid
pid: pid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: epoll
epoll: epoll.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: vector_io
vector_io: vector_io.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: mmap_io
mmap_io: mmap_io.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		stat \
		clocks \
		sched_info \
		pid \
		epoll \
		vector_io \
		mmap_io
