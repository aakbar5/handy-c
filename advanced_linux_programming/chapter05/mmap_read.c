// Listing 5.6 (mmap-read.c) Read an Integer from a Memory-Mapped File, and Double It

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

static const char* file_name = "write_test";
static const char* msg = "Hello world!";
static const int file_length = 1024 * 1;

//
// App entry point
//
int main()
{
  int ret;

  int fd = open(file_name, O_RDWR, S_IRUSR | S_IWUSR);
  check_status(fd > 0, "Fail to open file");

  (void)lseek(fd, 0, SEEK_SET);

  // Map file as mmap
  char *map = (char *)mmap(0, file_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  check_status(map, "Fail to mmap file");

  // Close file handle
  (void)close(fd);

  printf("Contents of the file:\n");
  printf("%s", map);
  printf("\n");

  // Write data to file
  sprintf(map + strlen(map), "\n%s\n", msg);

  // Unmap memory
  ret =  munmap(map, file_length);
  check_status(ret == 0, "Fail to munmap file");

  printf("File # %s is created, to see its contents, issue\n", file_name);
  printf(" cat %s\n", file_name);

  return 0;
}
