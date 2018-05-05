// Scatter/Gather I/O example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

#define NUMBER_OF_VECTORS   4
#define IO_VECTOR_SIZE      1024

int main() 
{
  int i;
  struct iovec iov[NUMBER_OF_VECTORS];

  printf("Scatter/Gather I/O Example\n");

  for (i = 0; i < NUMBER_OF_VECTORS; ++i) {
    iov[i].iov_base = malloc(IO_VECTOR_SIZE);
    iov[i].iov_len = IO_VECTOR_SIZE;
  }

  /* read data into multiple buffers */
  {
    int fd;
    ssize_t ret;

    /* Open file to read data */
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) {
      fprintf(stderr, "Fail to open file errno=%d\n", errno);
      fprintf(stderr, " - Error! %s\n", strerror(errno));
      return -1;
    }

    /* Read data into multiple buffers */
    ret =  readv(fd, iov, NUMBER_OF_VECTORS);
    printf("Number of bytes read: %ld\n", ret);

    /* Show each segment */
    for (i = 0; i < NUMBER_OF_VECTORS; ++i) {
      printf("---------------\n");
      printf("Segment # %d\n", i);
      printf("%s\n", (char *)iov[i].iov_base);
      printf("---------------\n");
    }

    close(fd);
  }

  /* write data into multiple buffers */
  {
    int fd;
    ssize_t ret;

    /* Open file to write data */
    fd = open("sample_write.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
      fprintf(stderr, "Fail to open file errno=%d\n", errno);
      fprintf(stderr, " - Error! %s\n", strerror(errno));
      return -1;
    }

    /* Write data into multiple buffers */
    ret =  writev(fd, iov, NUMBER_OF_VECTORS);
    printf("Number of bytes written: %ld\n", ret);

    close(fd);
  }

  for (i = 0; i < NUMBER_OF_VECTORS; ++i) {
    free(iov[i].iov_base);
  }

  return 0;
}
