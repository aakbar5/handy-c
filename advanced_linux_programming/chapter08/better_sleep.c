// Listing 8.8 (better_sleep.c) High-Precision Sleep Function

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

// Handy function to sleep using nanosleep
int nano_sleep(long milliseconds)
{
  struct timespec tv = {0};
  tv.tv_sec = (time_t) (milliseconds / 1000);
  tv.tv_nsec = (long) ((milliseconds - (tv.tv_sec * 1000L)) * 1e+6);

  while (1) {

    int ret =  nanosleep(&tv, &tv);
    if (ret == 0) {
      printf("nanosleep is complete\n");
      return 0;
    }
    else if (errno == EINTR) {
      printf("Paused is occurred (Error # %d (%s))\n", errno, strerror(errno));
      // try again
    }
    else {
      if (errno == EFAULT)         printf("User space problem (Error # %d (%s))\n", errno, strerror(errno));
      else if (errno == EINVAL)    printf("Invalid usec value (Error # %d (%s))\n", errno, strerror(errno));
      else                         printf("Error # %d (%s)\n", errno, strerror(errno));

      return errno;
    }
  }

  return -1;
}

//
// App entry point
//
int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: Specify sleep time in milliseconds\n");
    exit(0);
  }
  int ms = atoi(argv[1]);
  nano_sleep(ms);
  return 0;
}