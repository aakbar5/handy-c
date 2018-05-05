// Listing 7.6 (open-and-spin.c) Open a File for Reading

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//
// App entry point
//
int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: Pass process name to execute\n");
    exit(0);
  }

  const char* program = argv[1];
  int fd = open(program, O_RDONLY);
  printf("In process # %d file descriptor %d is open to %s\n", getpid(), fd, program);
  while(1) {}
  return 0;
}
