/**
 * Program
 *  A program to handle unix signals in a program. These signals
 *  can be seg fault, ctrl+c or any other standard unix signals.
 *  This program shows call stack and other info related to trapped signal.
 *
 * Compile
 *  gcc -Wall -Wextra signal_trap.c -o signal_trap
 *
 * Execution
 *  After execution, program will wait, while program is waiting,
 *  press CTRL+C to test this program
 *
 **/

#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Signal names */
const char *signal_names[] = {
  /*  0 */   "" ,
  /*  1 */   "SIGHUP" ,
  /*  2 */   "SIGINT" ,
  /*  3 */   "SIGQUIT" ,
  /*  4 */   "SIGILL" ,
  /*  5 */   "SIGTRAP" ,
  /*  6 */   "SIGABRT" ,
  /*  7 */   "SIGEMT" ,
  /*  8 */   "SIGFPE" ,
  /*  9 */   "SIGKILL" ,
  /* 10 */   "SIGBUS" ,
  /* 11 */   "SIGSEGV" ,
  /* 12 */   "SIGSYS" ,
  /* 13 */   "SIGPIPE" ,
  /* 14 */   "SIGALRM" ,
  /* 15 */   "SIGTERM" ,
  /* 16 */   "SIGUSR1" ,
  /* 17 */   "SIGUSR2" ,
  /* 18 */   "SIGCHLD" ,
  /* 19 */   "SIGPWR" ,
  /* 20 */   "SIGWINCH" ,
  /* 21 */   "SIGURG" ,
  /* 22 */   "SIGPOLL" ,
  /* 23 */   "SIGSTOP" ,
  /* 24 */   "SIGTSTP" ,
  /* 25 */   "SIGCONT" ,
  /* 26 */   "SIGTTIN" ,
  /* 27 */   "SIGTTOU" ,
  /* 28 */   "SIGVTALRM" ,
  /* 29 */   "SIGPROF" ,
  /* 30 */   "SIGXCPU" ,
  /* 31 */   "SIGXFSZ" ,
  /* 32 */   "SIGWAITING" ,
  /* 33 */   "SIGLWP" ,
  /* 34 */   "SIGAIO"
};

/**
 * Signal handler
 */
static void segfault_signal_trap(int signal, siginfo_t *si, void *arg)
{
  printf("\n\nSignal # %d(%s) is trapped\n", signal, signal_names[signal]);

  {
    printf("Signal Info:\n");
    printf("  Signal number       %d\n", si->si_signo);
    printf("  Signal error number %d\n", si->si_errno);
    printf("  Signal code         %d\n", si->si_code);
    printf("  Process Id          %ld\n", (long)si->si_pid);
    printf("  User Id             %ld\n", (long)si->si_uid);
    printf("  Consumed time(usr)  %g\n", (double)si->si_utime / (double)CLOCKS_PER_SEC);
    printf("  Consumed time(sys)  %g\n", (double)si->si_stime / (double)CLOCKS_PER_SEC);
    printf("\n");
  }

  {
    printf("Callstack:\n");
    const int callstack_len = 256;
    int i, number_of_frames;
    void **callstack = malloc(callstack_len * sizeof(void*));

    /* Get backtrace for the calling program */
    number_of_frames = backtrace(callstack, callstack_len);

    /* Translates addresses into readable string */
    char** backtrace_line = backtrace_symbols(callstack, number_of_frames);

    /* Print all backtrace lines */
    for (i = 0; i < number_of_frames; ++i) {
      printf("%s\n", backtrace_line[i]);
    }

    free(backtrace_line);

    printf("\n");
  }

  /* Suppress compiler warning(s) */
  (void)arg;

  printf ("\nDoing graceful shutdown of the application\n");
  exit(0);
}

/**
 * Install signal trap
 */
static void install_signal_trap(void)
{
  struct sigaction sa;

  memset(&sa, 0, sizeof(struct sigaction));
  sigemptyset(&sa.sa_mask);
  sa.sa_sigaction = segfault_signal_trap;
  sa.sa_flags = SA_SIGINFO;

  /* Ref: http://man7.org/linux/man-pages/man7/signal.7.html for available signals */
  sigaction(SIGSEGV, &sa, NULL);      /* Trap seg fault */
  sigaction(SIGINT, &sa, NULL);       /* Trap quit from keyboard */
}

/**
 * Entry function
 */
int main()
{
  printf("Hello world -- signal trapping\n");

  /* Install trap */
  install_signal_trap();

  printf("Waiting for user input...\n");
  while (1) {}

  printf("Good bye!\n");

  return 0;
}
