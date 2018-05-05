// Listing 8.2 (lock-file.c) Create a Write Lock with fcntl

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unwind.h>
#include <stdlib.h>
#include <unistd.h>

//
// App entry point
//
int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: Specify a test file\n");
    exit(0);
  }

  const char *file = argv[1];
  int fd = open(file, O_WRONLY);
  if (fd > 0)
  {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    printf("locking...\n");
    /* Setup WR lock */
    lock.l_type = F_WRLCK;
    fcntl(fd, F_SETLKW, &lock);
    printf("File is locked for WR\n");
    printf("locked: hit enter to unlock\n");
    getchar();

    printf("Unlock the file");
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);

    close(fd);
    printf("File is closed\n");
  }
  else
  {
    printf("Unable to open file\n");
  }

  return 0;
}
