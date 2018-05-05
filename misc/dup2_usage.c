/**
 * Program
 *  A simple use case of DUP2.
 *
 * Compile
 *  gcc -Wall -Wextra dup2_usage.c -o dup2_usage
 *
 * Execution
 *  ./dup2_usage
 **/

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

/**
 * Entry function
 */
int main ()
{
  const char* msg = "Text written by standard file descriptor\n";

  /* Open a file */
  int fd = open("dup2_test.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  check_status(fd != -1, "Fail to create file");

  /* Map stdout to our file */
  int nfd = dup2(fd, STDOUT_FILENO);
  check_status(nfd != -1, "Fail to dup2");

  /* Write text to a file */
  (void)lseek(fd, 0, SEEK_SET);
  (void)write(fd, msg, strlen(msg));

  printf("Text written by dup @ stdout file descriptor\n");

  /* Close file */
  int ret =  close(fd);
  check_status(ret == 0, "Fail to close file");

  return 0;
}
