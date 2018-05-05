// Listing 8.5 (print-cpu-times.c) Display Process User and System Times

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

//
// App entry point
//
int main()
{
  struct rusage usage = {0};
  getrusage(RUSAGE_SELF, &usage);

  printf("maximum resident set size        : %ld\n", usage.ru_maxrss);
  printf("integral shared memory size      : %ld\n", usage.ru_ixrss);
  printf("integral unshared data size      : %ld\n", usage.ru_idrss);
  printf("integral unshared stack size     : %ld\n", usage.ru_isrss);
  printf("page reclaims (soft page faults) : %ld\n", usage.ru_minflt);
  printf("page faults (hard page faults)   : %ld\n", usage.ru_majflt);
  printf("swaps                            : %ld\n", usage.ru_nswap);
  printf("block input operations           : %ld\n", usage.ru_inblock);
  printf("block output operations          : %ld\n", usage.ru_oublock);
  printf("IPC messages sent                : %ld\n", usage.ru_msgsnd);
  printf("IPC messages received            : %ld\n", usage.ru_msgrcv);
  printf("signals received                 : %ld\n", usage.ru_nsignals);
  printf("voluntary context switches       : %ld\n", usage.ru_nvcsw);
  printf("involuntary context switches     : %ld\n", usage.ru_nivcsw);

  return 0;
}
