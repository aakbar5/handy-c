// Listing 2.5 (temp_file.c) Using mkstemp
// - Create a unique file
// - On the first line write length of text

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//
// App entry point
//
int main()
{
  char file_name[] = "/tmp/linux_book_XXXXXX";

  /* Setup unique name file */
  int fd = mkstemp(file_name);
  if (fd == -1) {
    fprintf(stderr, "Fail to open temp file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    return -1;
  }

  printf("File name: %s\n", file_name);

  /* Delete the file if no process is using it */
  int ret = unlink(file_name);
  if (ret != 0) {
    fprintf(stderr, "Fail to unlink temp file errno=%d\n", errno);
    fprintf(stderr, " - Error! %s\n", strerror(errno));
    return -1;
  }

  const char* wtext = "Hello world! Advanced Linux Programming";
  ssize_t wlen = strlen(wtext);

  {
    /* Write length of the data */
    ssize_t len = write(fd, &wlen, sizeof(wlen));
    if (len != sizeof(wlen)) {
      fprintf(stderr, "Fail to write data\n");
      return -1;
    }

    /* Write actual data */
    len = write(fd, wtext, wlen);
    if (len != wlen) {
      fprintf(stderr, "Fail to write data\n");
      return -1;
    }

    printf("Write data: %s\n", wtext);
  }

  {
    /* Seek to the start of the file */
    lseek(fd, 0, SEEK_SET);

    /* Read length of the data */
    ssize_t rlen = 0;
    ssize_t l = read(fd, &rlen, sizeof(rlen));
    if (l != sizeof(rlen)) {
      fprintf(stderr, "Fail to read data\n");
      return -1;
    }

    char *rtext = (char *)malloc(sizeof(char) * rlen);
    if (rtext == NULL) {
      fprintf(stderr, "Unable to allocate memory\n");
      return -1;
    }

    l = read(fd, rtext, rlen);
    if (l != rlen) {
      fprintf(stderr, "Fail to read data\n");
      free(rtext);
      return -1;
    }

    printf("Read data:  %s\n", rtext);
    free(rtext);
  }

  close(fd);

  return 0;
}
