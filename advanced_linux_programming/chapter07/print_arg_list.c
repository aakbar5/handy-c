// Listing 7.3 (print-arg-list.c) Print the Argument List of a Running Process

#include <stdio.h>
#include <stdlib.h>

//
// App entry point
//
int main(int argc, char *argv[])
{
  const size_t len = 10;
  char buffer[len];

  if (argc < 2) {
    printf("Usage pass pid of the process to inspect\n");
    exit(0);
  }

  int pid = atoi(argv[1]);
  char process[128];
  sprintf(process, "/proc/%d/cmdline", pid);

  FILE *fp = fopen(process, "r");
  if (fp) {
    while (!feof(fp) &&  !ferror(fp)) {
      size_t rlen = fread(buffer, sizeof(char), len, fp);
      if (rlen == len) {
        buffer[len] = '\0';
      }

      printf("%s", buffer);
    }
    printf("\n");
    fclose(fp);
  }
  else {
    printf("Unable to find pid # %d\n", pid);
  }

  return 0;
}
