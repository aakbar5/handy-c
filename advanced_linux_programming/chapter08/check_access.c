// Listing 8.1 (check-access.c) Check File Access Permissions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

//
// App entry point
//
int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: Specify file path to check access\n");
    exit(0);
  }

  const char* file = argv[1];
  if (access(file, F_OK) == 0) {
    if (access(file, R_OK) == 0) printf("Read OK\n");
    if (access(file, W_OK) == 0) printf("Write OK\n");
    if (access(file, X_OK) == 0) printf("Execute OK\n");
  }
  else {
    printf("File does not exist\n");
  }

  return 0;
}
