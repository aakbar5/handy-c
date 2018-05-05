CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: bit_pos_loop

.PHONY: bit_pos_loop
bit_pos_loop: bit_pos_loop.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o bit_pos_loop bit_pos_loop.c

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
			bit_pos_loop
