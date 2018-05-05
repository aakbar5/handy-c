CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: shm \
	sem_all_deall \
	sem_init \
	sem_pv \
	mmap_write \
	mmap_read \
	pipe \
	dup2 \
	popen \
	socket_server \
	socket_client \
	socket_inet

.PHONY: shm
shm: shm.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: sem_all_deall
sem_all_deall: sem_all_deall.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: sem_init
sem_init: sem_init.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: sem_pv
sem_pv: sem_pv.o psem.o
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o sem_pv sem_pv.o psem.o

sem_pv.o: sem_pv.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -o sem_pv.o -c sem_pv.c

psem.o: psem.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o psem.o -c psem.c

.PHONY: mmap_write
mmap_write: mmap_write.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: mmap_read
mmap_read: mmap_read.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: pipe
pipe: pipe.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: dup2
dup2: dup2.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: popen
popen: popen.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: socket_server
socket_server: socket_server.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: socket_client
socket_client: socket_client.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: socket_inet
socket_inet: socket_inet.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		shm \
		sem_all_deall \
		sem_init \
		sem_pv \
		mmap_write \
		mmap_read \
		pipe \
		dup2 \
		popen \
		socket_server \
		socket_client \
		socket_inet
