// Listing 2.6 (readfile.c) Freeing Resources During Abnormal Conditions
// - Write a function which returns a buffer having text read from a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// Handy function to read file
static char* read_file(const char *file_name)
{
  int fd = open(file_name, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Fail to open file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    return NULL;
  }

  /* Seek to the end of file to calculate length */
  (void)lseek(fd, 0, SEEK_SET);
  off_t len = lseek(fd, 0, SEEK_END);
  if (len == -1) {
    fprintf(stderr, "Fail to seek file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    return NULL;
  }

  /* Allocate memory */
  char *buffer = (char *)malloc(sizeof(char) * len);
  if (!buffer) {
    fprintf(stderr, "Fail to allocate memory\n");
    close(fd);
    return NULL;
  }

  /* Move back to the start of the file */
  (void)lseek(fd, SEEK_SET, 0);

  /* Read file */
  ssize_t rlen = read(fd, buffer, len);
  if (len != rlen) {
    fprintf(stderr, "Fail to read data\n");
    free(buffer);
    close(fd);
    return NULL;
  }

  close(fd);
  return buffer;
}

//
// App entry point
//
int main()
{
  char* buffer = read_file("readfile_test.txt");
  if (buffer) {
    printf("Read data length: %ld\n", strlen(buffer));
    printf("Read data: %s\n", buffer);
    free(buffer);
  }

  return 0;
}
