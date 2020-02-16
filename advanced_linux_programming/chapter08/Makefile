CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: check_access \
	lock_file \
	write_journal_entry \
	limit_cpu \
	print_cpu_times \
	print_time \
	mprotect \
	better_sleep \
	print_symlink \
	copy \
	itemer \
	sysinfo \
	print_uname

.PHONY: check_access
check_access: check_access.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o check_access check_access.c

.PHONY: lock_file
lock_file: lock_file.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o lock_file lock_file.c

.PHONY: write_journal_entry
write_journal_entry: write_journal_entry.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o write_journal_entry write_journal_entry.c

.PHONY: limit_cpu
limit_cpu: limit_cpu.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o limit_cpu limit_cpu.c

.PHONY: print_cpu_times
print_cpu_times: print_cpu_times.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_cpu_times print_cpu_times.c

.PHONY: print_time
print_time: print_time.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_time print_time.c

.PHONY: mprotect
mprotect: mprotect.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o mprotect mprotect.c

.PHONY: better_sleep
better_sleep: better_sleep.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o better_sleep better_sleep.c

.PHONY: print_symlink
print_symlink: print_symlink.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_symlink print_symlink.c

.PHONY: copy
copy: copy.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o copy copy.c

.PHONY: itemer
itemer: itemer.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o itemer itemer.c

.PHONY: sysinfo
sysinfo: sysinfo.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o sysinfo sysinfo.c

.PHONY: print_uname
print_uname: print_uname.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o print_uname print_uname.c

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
			check_access \
			lock_file \
			write_journal_entry \
			limit_cpu \
			print_cpu_times \
			print_time \
			mprotect \
			better_sleep \
			print_symlink \
			copy \
			itemer \
			sysinfo \
			print_uname
