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
	test \
	app

.PHONY: arglist
arglist: arglist.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o arglist arglist.c

.PHONY: getopt_long
getopt_long: getopt_long.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o getopt_long getopt_long.c

.PHONY: print_env
print_env: print_env.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_env print_env.c

.PHONY: client
client: client.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o client client.c

.PHONY: temp_file
temp_file: temp_file.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o temp_file temp_file.c

.PHONY: readfile
readfile: readfile.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o readfile readfile.c

.PHONY: app
test: test.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c -o test.o test.c
	@echo "Archiving $@..."
	@$(AR) cr test.a test.o

app: test app.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o app app.c -L. test.a

.PHONY: tifftest
tifftest: tifftest.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o tifftest tifftest.c -lpng

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
	       arglist getopt_long print_env client \
		   temp_file readfile tifftest test app
