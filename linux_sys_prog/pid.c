// pid example

#include <stdio.h>
#include <unistd.h>

int main() 
{
  printf("pid example\n");
  printf("Pid of the process (current): %d\n", getpid());
  printf("Pid of the process (parent): %d\n", getppid());

  return 0;
}
