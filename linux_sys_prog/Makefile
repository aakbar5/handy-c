CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: vector_io

.PHONY: vector_io
vector_io: vector_io.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o vector_io vector_io.c

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
	       vector_io
