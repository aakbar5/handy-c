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
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: lock_file
lock_file: lock_file.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: write_journal_entry
write_journal_entry: write_journal_entry.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: limit_cpu
limit_cpu: limit_cpu.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_cpu_times
print_cpu_times: print_cpu_times.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_time
print_time: print_time.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: mprotect
mprotect: mprotect.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: better_sleep
better_sleep: better_sleep.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_symlink
print_symlink: print_symlink.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: copy
copy: copy.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: itemer
itemer: itemer.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: sysinfo
sysinfo: sysinfo.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: print_uname
print_uname: print_uname.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

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
