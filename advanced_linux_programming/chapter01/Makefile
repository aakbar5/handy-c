CC := gcc
CXX := g++

CXXFLAGS := -g -O0
CFLAGS := -g -O0

.PHONY: all
all: reciprocal

reciprocal: main.o reciprocal.o
	$(CXX) $(CXXFLAGS) -o reciprocal main.o reciprocal.o

main.o: main.c reciprocal.h
	$(CC) $(CFLAGS) -c main.c

reciprocal.o: reciprocal.c reciprocal.h
	$(CC) $(CFLAGS) -c reciprocal.c

.PHONY: clean
clean:
	rm -f *.o reciprocal
