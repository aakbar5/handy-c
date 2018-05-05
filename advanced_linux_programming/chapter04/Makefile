CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: thread_create \
	thread_create2 \
	thread_create2_2 \
	primes \
	detached \
	critical_section \
	tsd \
	cleanup \
	cxx_exit \
	job_queue1 \
	job_queue2 \
	job_queue3 \
	condvar \
	thread_pid

.PHONY: thread_create
thread_create: thread_create.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: thread_create2
thread_create2: thread_create2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: thread_create2_2
thread_create2_2: thread_create2_2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: primes
primes: primes.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: detached
detached: detached.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: critical_section
critical_section: critical_section.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: tsd
tsd: tsd.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: cleanup
cleanup: cleanup.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: cxx_exit
cxx_exit: cxx_exit.cpp
	@echo "Compiling $@"
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ -lpthread

.PHONY: job_queue1
job_queue1: job_queue1.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: job_queue2
job_queue2: job_queue2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: job_queue3
job_queue3: job_queue3.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: condvar
condvar: condvar.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: thread_pid
thread_pid: thread_pid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpthread

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		thread_create \
		thread_create2 \
		thread_create2_2 \
		primes \
		detached \
		critical_section \
		tsd \
		cleanup \
		cxx_exit \
		job_queue1 \
		job_queue2 \
		job_queue3 \
		condvar \
		thread_pid
