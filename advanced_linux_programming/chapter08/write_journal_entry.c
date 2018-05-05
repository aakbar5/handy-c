// Listing 8.3 (write_journal_entry.c) Write and Sync a Journal Entry

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//
// App entry point
//
int main()
{
  const char* file_name = "journal.log";
  int fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  write(fd, file_name, strlen(file_name));
  write(fd, "\n", 1);
  fsync(fd);
  close(fd);
  return 0;
}
