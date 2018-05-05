// Listing 8.9 (print-symlink.c) Print the Target of a Symbolic Link

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//
// App entry point
//
int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: Specify a test link file\n");
    exit(0);
  }

  const size_t len = 256;
  char buf[len];
  ssize_t le = readlink(argv[1], buf, len);
  if (le) {
    buf[le] = '\0';
    printf("Link is: %s\n", argv[1]);
    printf("File is: %s\n", buf);
  }
  else {
    printf("Error # %d (%s)\n", errno, strerror(errno));
  }

  return 0;
}
