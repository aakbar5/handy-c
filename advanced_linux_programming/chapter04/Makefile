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
	spin_condvar \
	condvar \
	thread_pid

.PHONY: thread_create
thread_create: thread_create.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o thread_create thread_create.c -lpthread

.PHONY: thread_create2
thread_create2: thread_create2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o thread_create2 thread_create2.c -lpthread

.PHONY: thread_create2_2
thread_create2_2: thread_create2_2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o thread_create2_2 thread_create2_2.c -lpthread

.PHONY: primes
primes: primes.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o primes primes.c -lpthread

.PHONY: detached
detached: detached.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o detached detached.c -lpthread

.PHONY: critical_section
critical_section: critical_section.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o critical_section critical_section.c -lpthread

.PHONY: tsd
tsd: tsd.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o tsd tsd.c -lpthread

.PHONY: cleanup
cleanup: cleanup.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o cleanup cleanup.c -lpthread

.PHONY: cxx_exit
cxx_exit: cxx_exit.cpp
	@echo "Compiling $@"
	@$(CXX) $(CFLAGS) -o cxx_exit cxx_exit.cpp -lpthread

.PHONY: job_queue1
job_queue1: job_queue1.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o job_queue1 job_queue1.c -lpthread

.PHONY: job_queue2
job_queue2: job_queue2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o job_queue2 job_queue2.c -lpthread

.PHONY: job_queue3
job_queue3: job_queue3.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o job_queue3 job_queue3.c -lpthread

.PHONY: spin_condvar
spin_condvar: spin_condvar.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o spin_condvar spin_condvar.c -lpthread

.PHONY: condvar
condvar: condvar.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o condvar condvar.c -lpthread

.PHONY: thread_pid
thread_pid: thread_pid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o thread_pid thread_pid.c -lpthread

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
		spin_condvar \
		condvar \
		thread_pid
