CC := gcc
CXX := g++
AR := ar

CXXFLAGS := -g -O0 -Wall -Wextra
CFLAGS := -g -O0 -Wall -Wextra

.PHONY: all
all: simpleid \
	 stat_perm \
	 setuid_test \
	 pam \
	 temp_file

.PHONY: simpleid
simpleid: simpleid.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: stat_perm
stat_perm: stat_perm.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: setuid_test
setuid_test: setuid_test.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: pam
pam: pam.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^
#	@$(CC) $(CFLAGS) -o $@ $^ -lpam -lpam_misc

.PHONY: temp_file
temp_file: temp_file.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo "Remove obj files..."
	@rm -f *.o *.a \
		simpleid \
		stat_perm \
		setuid_test \
		pam \
		temp_file