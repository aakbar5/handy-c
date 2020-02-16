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
	@$(CC) $(CFLAGS) -o print_pid print_pid.c

.PHONY: system
system: system.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o system system.c

.PHONY: fork
fork: fork.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o fork fork.c

.PHONY: fork_exec
fork_exec: fork_exec.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o fork_exec fork_exec.c

.PHONY: sigusr1
sigusr1: sigusr1.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o sigusr1 sigusr1.c

.PHONY: zombie
zombie: zombie.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o zombie zombie.c

.PHONY: sigchld
sigchld: sigchld.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o sigchld sigchld.c

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		print_pid system fork fork_exec \
		sigusr1 zombie sigchld
