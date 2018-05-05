CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: print_pid \
	system \
	fork \
	fork_exec \
	sigusr1 \
	zombie \
	sigchld

.PHONY: print_pid
print_pid: print_pid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: system
system: system.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: fork
fork: fork.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: fork_exec
fork_exec: fork_exec.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: sigusr1
sigusr1: sigusr1.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: zombie
zombie: zombie.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: sigchld
sigchld: sigchld.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		print_pid system fork fork_exec \
		sigusr1 zombie sigchld
