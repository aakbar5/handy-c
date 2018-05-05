// Listing 6.1 (random_number.c) Function to Generate a Random Number Using /dev/random
// Return a random integer between MIN and MAX, inclusive.
// randomness from /dev/random.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

// Handy function to read a number of /dev/random
static int read_number(int fd)
{
  int random_value;
  int len_to_read = sizeof(random_value);
  char *buffer = (char *)&random_value;

  while (len_to_read) {
    read(fd, buffer, 1);
    len_to_read -= 1;
    buffer += 1;
  }

  return random_value;
}

//
// App entry point
//
int main()
{
  const int min = 10;
  const int max = 20;
  const int limit = 50;

  int fd = open("/dev/random", O_RDWR, S_IRUSR | S_IWUSR);
  check_status(fd > 0, "Fail to open file");

  int count = 0;
  while (count < limit) {
    int random1 = read_number(fd);
    int random2 = min + (random1 % (max - min + 1));
    printf("Random number: %2d --- %d\n", random2, random1);
    ++count;
  }

  close(fd);
  return 0;
}
