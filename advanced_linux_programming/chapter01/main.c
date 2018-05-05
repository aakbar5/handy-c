#include <stdio.h>
#include <stdlib.h>
#include "reciprocal.h"

// Handy function to show usage
static void usage(FILE *fp, int argc, char **argv)
{
  fprintf(fp,
    "Calculate reciprocal of an integer value\n"
     "Usage: %s [options]\n"
     "<interger value> - Value whose reciprocal to be calculated\n",
     argv[0]
  );
}

//
// App entry point
//
int main(int argc, char* argv[])
{
  if (argc != 2) {
    usage(stderr, argc, argv);
    exit(EXIT_FAILURE);
  }

  int num = atoi(argv[1]);
  printf("Reciprocal of %d is %f\n\r", num, reciprocal(num));

  return 0;
}
