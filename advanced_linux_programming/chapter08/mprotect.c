// Listing 8.7 (mprotect.c) Detect Memory Access Using mprotect

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

static int page_size = 0;
static char* memory = NULL;

// Signal callback
static void signal_handler(int signal_number)
{
  printf("Seg fault (%d) is received\n", signal_number);

  // NOTE: If you don't provide write access
  // linux keeps on restarting app in a hope
  // that issue has been fixed
  // Put following line in comments to see it
  mprotect(memory, page_size, PROT_READ | PROT_WRITE);
}

//
// App entry point
//
int main()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof (sa));
  sa.sa_handler = &signal_handler;

  // Trap seg fault
  sigaction(SIGSEGV, &sa, NULL);

  page_size = getpagesize();

  printf("Map /dev/zero for %d\n", page_size);
  int fd = open("/dev/zero", O_RDONLY);
  memory = mmap(NULL, page_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
  close(fd);

  printf("Write mapped memory..\n");
  memory[0] = 0;

  printf("Memory is write protected\n");
  mprotect(memory, page_size, PROT_NONE);

  printf("Write mapped memory (Should have segfault)..\n");
  memory[0] = 0;

  printf("Unmap memory\n");
  munmap(memory, page_size);
  return 0;
}
