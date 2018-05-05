// schedular related info

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>

static void print_cpu_affinty(pid_t pid) 
{
  const long cores = sysconf(_SC_NPROCESSORS_ONLN);

  printf("\nAssigned CPU = %d\n", sched_getcpu());
  {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);

    int ret =  sched_getaffinity(pid, sizeof(cpu_set_t), &cpuset);
    if (ret < 0) {
      printf("Err! sched_getaffinity (errno = %d)\n", errno);
      return;
    }

    printf("CPU: ");
    for (int i = 0; i < cores; ++i) {
      printf("%2d ", i);
    }
    printf("\n");

    printf("     ");
    for (int i = 0; i < cores; ++i) {
      if (CPU_ISSET(i, &cpuset)) {
        printf("%2d ", 1);
      }
      else {
        printf("%2d ", 0);
      }
    }
    printf("\n");
  }
}

int main() 
{
  printf("schedular info example\n");

  const pid_t pid = getpid();
  const long cores = sysconf(_SC_NPROCESSORS_ONLN);
  const int policy = sched_getscheduler(pid);
  if (policy == 0) {
    switch (policy) {
      case SCHED_OTHER:
        printf("Current schedular policy is: %s\n", "SCHED_OTHER");
      break;

      case SCHED_FIFO:
        printf("Current schedular policy is: %s\n", "SCHED_FIFO");
      break;

      case SCHED_RR:
        printf("Current schedular policy is: %s\n", "SCHED_RR");
      break;

      default:
        printf("Current schedular policy is: %s:%d\n", "Unkown", policy);
      break;
    }
  }
  else {
    printf("Err! sched_getscheduler (errno = %d)\n", errno);
    return -1;
  }

  printf("Pid: %d\n", pid);
  printf("Number of cores: %ld\n", cores);
  printf("Schedular (SCHED_OTHER) max priority: %d\n", sched_get_priority_max(SCHED_OTHER));
  printf("Schedular (SCHED_OTHER) min priority: %d\n", sched_get_priority_min(SCHED_OTHER));
  printf("Schedular (SCHED_FIFO) max priority: %d\n", sched_get_priority_max(SCHED_FIFO));
  printf("Schedular (SCHED_FIFO) min priority: %d\n", sched_get_priority_min(SCHED_FIFO));
  printf("Schedular (SCHED_RR) max priority: %d\n", sched_get_priority_max(SCHED_RR));
  printf("Schedular (SCHED_RR) min priority: %d\n", sched_get_priority_min(SCHED_RR));

  print_cpu_affinty(pid);

  // Change cpu
  printf("change cpu...\n");
  {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(10, &cpuset);

    int ret =  sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset);
    if (ret < 0) {
      printf("Err! sched_setaffinity (errno = %d)\n", errno);
      return -1;
    }
  }

  print_cpu_affinty(pid);

  return 0;
}
