CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: random_number

default: random_number

.PHONY: random_number
random_number: random_number.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
			random_number
