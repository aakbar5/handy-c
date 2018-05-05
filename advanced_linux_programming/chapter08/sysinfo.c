// Listing 8.12 (sysinfo.c) Print System Statistics

#include <stdio.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <errno.h>

int main()
{
  struct sysinfo info;
  int ret =  sysinfo(&info);
  if (ret == -1)
    printf("Error # %d (%s)\n", errno, strerror(errno));

  printf("Number of current processes:   %d\n", info.procs);
  printf("Total swap space size:         %ld\n", info.totalswap);
  printf("Available memory size:         %ld\n", info.freeram);
  printf("Total usable main memory size: %ld\n", info.totalram);

  return 0;
}
