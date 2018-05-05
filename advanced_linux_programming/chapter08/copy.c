// Listing 8.10 (copy.c) File Copy Using sendfile

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

//
// App entry point
//
int main(int argc, char* argv[])
{
  if (argc < 3) {
    printf("Usage: </path/to/source/file> </path/to/dst/file>\n");
    exit(0);
  }

  int rfd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);
  if (rfd == -1) {
    printf("Unable to open source file\n");
    exit(0);
  }

  int wfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (rfd == -1) {
    printf("Unable to open write file\n");
    exit(0);
  }

  struct stat buf;
  if (fstat(rfd, &buf) == -1) {
    printf("Unable to stat the read file\n");
    exit(0);
  }

  ssize_t ret =  sendfile(wfd, rfd, NULL, buf.st_size);
  if (ret == -1)
    printf("Unable to sendfile\n");
  else
    printf("File is copied\n");

  close(rfd);
  close(wfd);

  return 0;
}