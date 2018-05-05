// Listing 2.3 ( print-env.c) Printing the Execution Environment

#include <stdio.h>

// http://man7.org/linux/man-pages/man7/environ.7.html
extern char** environ;

//
// App entry point
//
int main()
{
  char **var;
  int idx = 1;
  for (var = environ, idx = 1; *var != NULL; ++var, ++idx) {
      printf("#%2d -- %s\n", idx, *var);
  }

  return 0;
}
