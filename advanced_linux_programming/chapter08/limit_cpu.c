// Listing 8.4 (limit-cpu.c) CPU Time Limit Demonstration

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

//
// App entry point
//
int main()
{
  struct rlimit lim = {0};
  getrlimit(RLIMIT_CPU, &lim);
  printf("Cpu limit (soft): %ld\n", lim.rlim_cur);
  printf("Cpu limit (hard): %ld\n", lim.rlim_max);

  lim.rlim_cur = 1; // Set limit to 1 second
  setrlimit(RLIMIT_CPU, &lim);

  while (1);

  return 0;
}
