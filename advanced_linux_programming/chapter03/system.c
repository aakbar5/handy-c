// Listing 3.2 (system.c) Using the system Call
// - Launch an external programing using system call

#include <stdio.h>
#include <stdlib.h>

//
// App entry point
//
int main()
{
  int ret =  system("ls -l /");
  printf("Return value of system: %d\n", ret);
  return 0;
}
