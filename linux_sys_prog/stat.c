// stat example

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <errno.h>

int main() 
{
  printf("stat example\n");

  char *file = "sample.txt";
  struct stat sb = {};
  int ret;

  ret =  access(file, F_OK | R_OK | W_OK);
  if (ret == -1) {
    printf("Err! sched_getscheduler (errno = %d)\n", errno);
    return -1;
  }

  ret =  stat(file, &sb);
  if (ret == -1) {
    printf("Err! sched_getscheduler (errno = %d)\n", errno);
    return -1;
  }

  printf("File:                     %s\n", file);
  printf("File size:                %ld bytes\n", (intmax_t) sb.st_size);
  printf("Preferred I/O block size: %ld bytes\n", (intmax_t) sb.st_blksize);
  printf("Blocks allocated:         %ld\n", (intmax_t) sb.st_blocks);
  printf("Ownership:                GID=%lu, UID=%lu\n", (uintmax_t) sb.st_gid, (uintmax_t) sb.st_uid);

  printf("Last file access:         %s", ctime(&sb.st_atime));
  printf("Last status change:       %s", ctime(&sb.st_ctime));
  printf("Last file modification:   %s", ctime(&sb.st_mtime));
  printf("File type:                ");
  switch (sb.st_mode & S_IFMT) {
    case S_IFLNK:  printf("Symlink\n");          break;
    case S_IFREG:  printf("Regular file\n");     break;
    case S_IFSOCK: printf("Socket\n");           break;
    case S_IFBLK:  printf("Block device\n");     break;
    case S_IFCHR:  printf("Character device\n"); break;
    case S_IFDIR:  printf("Directory\n");        break;
    case S_IFIFO:  printf("FIFO/pipe\n");        break;
    default:       printf("Unknown\n");          break;
  }
  
  return 0;
}
