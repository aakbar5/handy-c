// Usage example of different cocks

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x[0])))

struct {
  clockid_t id;
  char name[50];
} clocks[] = {
  { CLOCK_REALTIME, "CLOCK_REALTIME" },
  { CLOCK_MONOTONIC, "CLOCK_MONOTONIC" },
  // { CLOCK_REALTIME_HR, "CLOCK_REALTIME_HR" },
  // { CLOCK_MONOTONIC_HR, "CLOCK_MONOTONIC_HR" },
  { CLOCK_PROCESS_CPUTIME_ID, "CLOCK_PROCESS_CPUTIME_ID" },
  { CLOCK_THREAD_CPUTIME_ID, "CLOCK_THREAD_CPUTIME_ID" },
  { CLOCK_MONOTONIC_RAW, "CLOCK_MONOTONIC_RAW" },
};

int main() 
{
  printf("clocks example\n");

  time_t now;
  now = time(&now);
  printf ("Time since the epoch: %ld seconds\n", (size_t)now);

  struct timeval timev;
  gettimeofday(&timev, NULL);
  printf ("Time of the day: %ld sec, %ld usec\n", (size_t)timev.tv_sec, (size_t)timev.tv_usec);

  printf("\n");
  for (size_t idx = 0; idx < ARRAY_SIZE(clocks); ++idx) {

    const clockid_t id = clocks[idx].id;
    const char* name = clocks[idx].name;
    struct timespec ts;

    printf("%s\n", name);

    int ret =  clock_getres(id, &ts);
    if (ret < 0) {
      printf("Err! clock_getres (errno = %d)\n", errno);
      continue;
    }
    printf("  %12s: %lds, %ldns\n", "Resolution", (size_t)ts.tv_sec, ts.tv_nsec);

    ret =  clock_gettime(id, &ts);
    if (ret < 0) {
      printf("Err! clock_gettime (errno = %d)\n", errno);
      continue;
    }
    printf("  %12s: %lds, %ldns\n", "Time", (size_t)ts.tv_sec, ts.tv_nsec);
  }

  return 0;
}
