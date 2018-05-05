<!-- TOC -->

- [Info](#info)
- [Chapter 01](#chapter-01)
- [Chapter 02](#chapter-02)
- [Chapter 03](#chapter-03)
- [Chapter 04](#chapter-04)
- [Chapter 05](#chapter-05)
- [Chapter 06](#chapter-06)
- [Chapter 07](#chapter-07)
- [Chapter 08](#chapter-08)
- [Chapter 09](#chapter-09)
- [Chapter 10](#chapter-10)
- [Chapter 11](#chapter-11)

<!-- /TOC -->

# Info
Book # Advanced Linux Programming
By Mark Mitchell, Jeffrey Oldham, and Alex Samuel

# Chapter 01
- Listing 1.1  [main.c](chapter01/main.c) C source file - main.c
- Listing 1.2  [reciprocal.c](chapter01/reciprocal.c) C source file reciprocal
- Listing 1.3  [reciprocal.h](chapter01/reciprocal.h) Header file reciprocal.h

# Chapter 02
- Listing 2.1   [arglist.c](chapter02/arglist.c) Demonstrates how to use argc and argv.
- Listing 2.2   [getopt_long.c](chapter02/getopt_long.c) Using getopt_long
- Listing 2.3   [print_env.c](chapter02/print_env.c) Printing the Execution Environment
- Listing 2.4   [client.c](chapter02/client.c) Part of a Network Client Program
- Listing 2.5   [temp_file.c](chapter02/temp_file.c) Using mkstemp
- Listing 2.6   [readfile.c](chapter02/readfile.c) Freeing Resources During Abnormal Conditions
- Listing 2.7   [test.c](chapter02/test.c) Library Contents
- Listing 2.8   [app.c](chapter02/app.c) A Program That Uses Library Functions
- Listing 2.9   [tifftest.c](chapter02/tifftest.c) Using libtiff

# Chapter 03
- Listing 3.1   [print_pid.c](chapter03/print_pid.c) Printing the Process ID
- Listing 3.2   [system.c](chapter03/system.c) Using the system Call
- Listing 3.3   [fork.c](chapter03/fork.c) Using fork to Duplicate a Program’s Process
- Listing 3.4   [fork_exec.c](chapter03/fork_exec.c) Using fork and exec Together
- Listing 3.5   [sigusr1.c](chapter03/sigusr1.c) Using a Signal Handler
- Listing 3.6   [zombie.c](chapter03/zombie.c) Making a Zombie Process
- Listing 3.7   [sigchld.c](chapter03/sigchld.c) Cleaning Up Children by Handling SIGCHLD

# Chapter 04
- Listing 4.1   [thread_create.c](chapter04/thread_create.c) Create a Thread
- Listing 4.2   [thread_create2.c](chapter04/thread_create2.c) Create Two Threads and pass data to each
- Listing 4.3   [thread_create2_2.c](chapter04/thread_create2_2.c) Revised Main Function for thread_create2.c
- Listing 4.4   [primes.c](chapter04/primes.c) Compute Prime Numbers in a Thread
- Listing 4.5   [detached.c](chapter04/detached.c) Skeleton Program That Creates a Detached Thread
- Listing 4.6   [critical_section.c](chapter04/critical_section.c) Protect a Bank Transaction with a Critical Section
- Listing 4.7   [tsd.c](chapter04/tsd.c) Per-Thread Log Files Implemented with Thread-Specific Data
- Listing 4.8   [cleanup.c](chapter04/cleanup.c) Program Fragment Demonstrating a Thread Cleanup Handler
- Listing 4.9   [cxx_exit.cpp](chapter04/cxx_exit.cpp) Implementing Safe Thread Exit with C++ Exceptions
- Listing 4.10  [job_queue1.c](chapter04/job_queue1.c) Thread Function to Process Jobs from the Queue
- Listing 4.11  [job_queue2.c](chapter04/job_queue2.c) Job Queue Thread Function, Protected by a Mutex
- Listing 4.12  [job_queue3.c](chapter04/job_queue3.c) Job Queue Controlled by a Semaphore
- Listing 4.13  [spin_condvar.c](chapter04/spin_condvar.c) A Simple Condition Variable Implementation
- Listing 4.14  [condvar.c](chapter04/condvar.c) Control a Thread Using a Condition Variable
- Listing 4.15  [thread_pid.c](chapter04/thread_pid.c) Print Process IDs for Threads

# Chapter 05
- Listing 5.1   [shm.c](chapter05/shm.c) Exercise Shared Memory
- Listing 5.2   [sem_all_deall.c](chapter05/sem_all_deall.c) Allocating and Deallocating a Binary Semaphore
- Listing 5.3   [sem_init.c](chapter05/sem_init.c) Initializing a Binary Semaphore
- Listing 5.4   [sem_pv.c](chapter05/sem_pv.c) Wait and Post Operations for a Binary Semaphore
- Listing 5.5   [mmap_write.c](chapter05/mmap_write.c) Write a Random Number to a Memory-Mapped File
- Listing 5.6   [mmap_read.c](chapter05/mmap_read.c) Read an Integer from a Memory-Mapped File, and Double It
- Listing 5.7   [pipe.c](chapter05/pipe.c) Using a Pipe to Communicate with a Child Process
- Listing 5.8   [dup2.c](chapter05/dup2.c) Redirect Output from a Pipe with dup2
- Listing 5.9   [popen.c](chapter05/popen.c) Example Using popen
- Listing 5.10  [socket_server.c](chapter05/socket_server.c) Local Namespace Socket Server
- Listing 5.11  [socket_client.c](chapter05/socket_client.c) Local Namespace Socket Client
- Listing 5.12  [socket_inet.c](chapter05/socket_inet.c) Read from a WWW Server

# Chapter 06
- Listing 6.1   [random_number.c](chapter06/random_number.c) Function to Generate a Random Number Using /dev/random
- Listing 6.2   [cdrom_eject.c](chapter06/cdrom_eject.c) Eject a CD_ROM

# Chapter 07
- Listing 7.1   [clock_speed.c](chapter07/clock_speed.c) Extract CPU Clock Speed from /proc/cpuinfo
- Listing 7.2   [get_pid.c](chapter07/get_pid.c) Obtain the Process ID from /proc/self
- Listing 7.3   [print_arg_list.c](chapter07/print_arg_list.c) Print the Argument List of a Running Process
- Listing 7.4   [print_environment.c](chapter07/print_environment.c) Display the Environment of a Process
- Listing 7.5   [get_exe_path.c](chapter07/get_exe_path.c) Get the Path of the Currently Running Program Executable
- Listing 7.6   [open_and_spin.c](chapter07/open_and_spin.c) Open a File for Reading
- Listing 7.7   [print_uptime.c](chapter07/print_uptime.c) Print the System Uptime and Idle Time

# Chapter 08
- Listing 8.1   [check_access.c](chapter08/check_access.c) Check File Access Permissions
- Listing 8.2   [lock_file.c](chapter08/lock_file.c) Create a Write Lock with fcntl
- Listing 8.3   [write_journal_entry.c](chapter08/write_journal_entry.c) Write and Sync a Journal Entry
- Listing 8.4   [limit_cpu.c](chapter08/limit_cpu.c) CPU Time Limit Demonstration
- Listing 8.5   [print_cpu_times.c](chapter08/print_cpu_times.c) Display Process User and System Times
- Listing 8.6   [print_time.c](chapter08/print_time.c) Print Date and Time
- Listing 8.7   [mprotect.c](chapter08/mprotect.c) Detect Memory Access Using mprotect
- Listing 8.8   [better_sleep.c](chapter08/better_sleep.c) High_Precision Sleep Function
- Listing 8.9   [print_symlink.c](chapter08/print_symlink.c) Print the Target of a Symbolic Link
- Listing 8.10  [copy.c](chapter08/copy.c) File Copy Using sendfile
- Listing 8.11  [itemer.c](chapter08/itemer.c) Timer Example
- Listing 8.12  [sysinfo.c](chapter08/sysinfo.c) Print System Statistics
- Listing 8.13  [print_uname.c](chapter08/print_uname.c) Print Linux Version Number and Hardware Information

# Chapter 09
- Listing 9.1   [bit_pos_loop.c](chapter09/bit_pos_loop.c) Find Bit Position Using a Loop
- Listing 9.2   [bit_pos_asm.c](chapter09/bit_pos_asm.c) Find Bit Position Using bsrl

# Chapter 10
- Listing 10.1  [simpleid.c](chapter10/simpleid.c) Print User and Group IDs
- Listing 10.2  [stat_perm.c](chapter10/stat_perm.c) Determine File Owner’s Write Permission
- Listing 10.3  [setuid_test.c](chapter10/setuid_test.c) Setuid Demonstration Program
- Listing 10.4  [pam.c](chapter10/pam.c) PAM Example
- Listing 10.5  [temp_file.c](chapter10/temp_file.c) Create a Temporary File
- Listing 10.6  [grep_dictionary.c](chapter10/grep_dictionary.c) Search for a Word in the Dictionary

# Chapter 11
- Listing 11.1  [server.c](chapter11/server.h) Function and Variable Declarations
- Listing 11.2  [common.c](chapter11/common.c) General Utility Functions
- Listing 11.3  [module.c](chapter11/module.c) Server Module Loading and Unloading
- Listing 11.4  [server.c](chapter11/server.c) Server Implementation
- Listing 11.5  [main.c](chapter11/main.c) Main Server Program and Command_Line Parsing
- Listing 11.6  [time.c](chapter11/time.c) Server Module to Show Wall_Clock Time
- Listing 11.7  [issue.c](chapter11/issue.c) Server Module to Display GNU/Linux Distribution Information
- Listing 11.8  [diskfree.c](chapter11/diskfree.c) Server Module to Display Information About Free Disk Space
- Listing 11.9  [processes.c](chapter11/processes.c) Server Module to Summarize Processes
- Listing 11.10 [Makefile](chapter11/Makefile) GNU Make Configuration File for Server Example
