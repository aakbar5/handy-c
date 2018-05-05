// Listing 8.11 (itemer.c) Timer Example

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

// Signal to monitor timer callback
static sig_atomic_t timer_expiry_count = 0;

// Signal callback
static void signal_handler(int signal_number)
{
  printf("Signal # %d is received\n", signal_number);
  ++timer_expiry_count;
}

//
// App entry point
//
int main()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof (sa));
  sa.sa_handler = &signal_handler;

  // Trap signal
  sigaction(SIGVTALRM, &sa, NULL);

  struct itimerval timer;

  // Interval for periodic timer
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 300000; /* 300 ms */

  // Time until next expiration
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 250000; /* 250 ms */

  int ret =  setitimer(ITIMER_VIRTUAL, &timer, NULL);
  if (ret == -1)
    printf("Error # %d (%s)\n", errno, strerror(errno));

  // Wait for atleast 10 timer expiry
  while(timer_expiry_count < 10) {}

  printf("Good bye!\n");
  return 0;
}
