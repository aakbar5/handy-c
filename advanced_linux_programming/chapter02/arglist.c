// Listing 2.1 demonstrates how to use argc and argv.

#include <stdio.h>

//
// App entry point
//
int main(int argc, char* argv[])
{
  for (int i = 0; i < argc; ++i) {
    printf(" Parameter # %3d -- %s\n", i+1, argv[i]);
  }

  return 0;
}
