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
	@$(CC) $(CFLAGS) -o clock_speed clock_speed.c

.PHONY: get_exe_path
get_exe_path: get_exe_path.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o get_exe_path get_exe_path.c

.PHONY: get_pid
get_pid: get_pid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o get_pid get_pid.c

.PHONY: print_arg_list
print_arg_list: print_arg_list.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_arg_list print_arg_list.c

.PHONY: print_environment
print_environment: print_environment.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_environment print_environment.c

.PHONY: open_and_spin
open_and_spin: open_and_spin.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o open_and_spin open_and_spin.c

.PHONY: print_uptime
print_uptime: print_uptime.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_uptime print_uptime.c

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
