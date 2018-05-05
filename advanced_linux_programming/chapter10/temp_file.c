// Listing 10.5 (temp-file.c) Create a Temporary File
//
// Returns the file descriptor for a newly created temporary file.
// The temporary file will be readable and writable by the effective
// user ID of the current process but will not be readable or
// writable by anybody else.
// Returns -1 if the temporary file could not be created.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static const int name_length = 128;

// Handy function to generate unique name
int generate_temp_file(char *name)
{
  int fd_random = open("/dev/random", O_RDWR, S_IRUSR | S_IWUSR);
  if (fd_random == -1) {
    printf("Fail to open /dev/random (errno=%d, %s)\n", errno, strerror(errno));
    return -1;
  }

  int random_number;
  if (read(fd_random, &random_number, sizeof(int)) != sizeof(int)) {
    printf("Fail to read required length of data (errno=%d, %s)\n", errno, strerror(errno));
    return -1;
  }

  char file[name_length];
  strcpy(file, "/tmp/");

  if (name)
    sprintf(file + strlen(file), "%s", name);

  sprintf(file + strlen(file), "%d", random_number);

  // NOTE: O_EXCL is not available for NFS
  int fd_tmp = open(file, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
  if (fd_tmp == -1) {
    printf("Fail to open tmp file (errno=%d, %s)\n", errno, strerror(errno));
    return -1;
  }

  struct stat buf;
  if (fstat(fd_tmp, &buf) == -1) {
    printf("Fail to fstat (errno=%d, %s)\n", errno, strerror(errno));
    return -1;
  }

  // Is it link?
  if (!S_ISREG(buf.st_mode)) {
    printf("Hacked! File is link\n");
    return -1;
  }

  // Do we own it?
  if (buf.st_uid != geteuid () || buf.st_gid != getegid ()) {
    printf("Hacked! We don't own it\n");
    return -1;
  }

  // Is there any change is permissions
  if ((buf.st_mode & (S_IRUSR | S_IWUSR)) != (S_IRUSR | S_IWUSR)) {
    printf("Hacked! permissions are changed\n");
    return -1;
  }

  return fd_tmp;
}

//
// App entry point
//
int main()
{
  int fd = generate_temp_file(NULL);
  if (fd != -1) {
    write(fd, "A", 1);
    close(fd);
  }
  return 0;
}
