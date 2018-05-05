// Listing 3.1 ( print-pid.c) Printing the Process ID

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//
// App entry point
//
int main()
{
  printf("Process Id:          %d\n", getpid());
  printf("Process Id (Parent): %d\n", getppid());
  return 0;
}
