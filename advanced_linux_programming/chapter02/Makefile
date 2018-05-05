CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: arglist \
	getopt_long \
	print_env client \
	temp_file \
	readfile \
	tifftest \
	app

.PHONY: arglist
arglist: arglist.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: getopt_long
getopt_long: getopt_long.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_env
print_env: print_env.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: client
client: client.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: temp_file
temp_file: temp_file.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: readfile
readfile: readfile.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

test.a: test.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c -o test.o test.c
	@echo "Archiving $@..."
	@$(AR) cr test.a test.o

.PHONY: app
app: test.a app.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o app app.c -L. test.a

.PHONY: tifftest
tifftest: tifftest.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^ -lpng

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
	       arglist getopt_long print_env client \
		   temp_file readfile tifftest test app
