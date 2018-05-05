// mmap example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main() 
{
  int fd, ret, idx;
  struct stat fdinfo;
  char *ptr;

  printf("mmap example\n");

  /* Open file to read data */
  fd = open("sample.txt", O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Fail to open file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    return -1;
  }

  /* stat the given file */
  ret =  fstat(fd, &fdinfo);
  if (ret == -1) {
    fprintf(stderr, "Fail to stat file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    goto err_ret;
  }

  if (!S_ISREG(fdinfo.st_mode)) {
    fprintf(stderr, "Given file is not regular file\n");
    goto err_ret;
  }

  printf("File size: %lld bytes\n", (long long)fdinfo.st_size);

  /* Map the whole file */
  ptr = (char *)mmap(0, fdinfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    fprintf(stderr, "Fail to map file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    goto err_ret;
  }

  /* Show the contents */
  for (idx = 0; idx < fdinfo.st_size; ++idx) {
    printf("%c", ptr[idx]);
    if ((idx + 1) % 32 == 0)
      printf("\n\r");
  }

  munmap(ptr, fdinfo.st_size);
  close(fd);
  return 0;

err_ret:
  close(fd);
  return -1;
}
