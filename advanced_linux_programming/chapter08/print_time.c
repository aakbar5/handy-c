// Listing 8.6 (print-time.c) Print Date and Time

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
  struct timeval tv;
  char buff[128];

  gettimeofday(&tv, NULL);

  struct tm *time = localtime(&tv.tv_sec);
  strftime(buff, sizeof buff, "%A %c", time);
  printf("%s\n", buff);
  return 0;
}