CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: clock_speed \
	get_pid \
	print_arg_list \
	print_environment \
	get_exe_path \
	open_and_spin \
	print_uptime

.PHONY: clock_speed
clock_speed: clock_speed.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: get_exe_path
get_exe_path: get_exe_path.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: get_pid
get_pid: get_pid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_arg_list
print_arg_list: print_arg_list.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_environment
print_environment: print_environment.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: open_and_spin
open_and_spin: open_and_spin.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_uptime
print_uptime: print_uptime.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		clock_speed \
		get_pid \
		print_arg_list \
		print_environment \
		get_exe_path \
		open_and_spin \
		print_uptime
