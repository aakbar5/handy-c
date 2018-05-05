// Listing 3.5 (sigusr1.c) Using a Signal Handler

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/* Use sig_atomic_t for global variable manipulated in
   signal handler for atomicity otherwise it may be corrupted
   if multiple signals are occurred */
static sig_atomic_t fault_count = 0;
static sig_atomic_t int_count = 0;

// Signal callback
static void signal_handler(int signal_number)
{
  if (signal_number == SIGSEGV)
    ++fault_count;
  else if (signal_number == SIGINT)
    ++int_count;
}

//
// App entry point
//
int main()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof (sa));
  sa.sa_handler = &signal_handler;

  /* Ref: http://man7.org/linux/man-pages/man7/signal.7.html for available signals */
  sigaction(SIGSEGV, &sa, NULL);      /* Trap seg fault */
  sigaction(SIGINT, &sa, NULL);       /* Trap quit from keyboard */

  // Keep on running until ctrl+c has not been passed 10 times
  while (int_count < 10) {
    printf("[SEG fault = %4d][INT fault = %4d]\n", fault_count, int_count);
    usleep(200);
  }

  return 0;
}
