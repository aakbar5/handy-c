// Listing 7.1 (clock-speed.c) Extract CPU Clock Speed from /proc/cpuinfo

#include <stdio.h>
#include <string.h>

// Handy function to parse cpu clock
char* find_cpu_clock(char *text)
{
  char *found = strstr(text, "cpu MHz");
  if (found) {
    char *token = strtok(found, ":");
    while(token) {
      token = strtok(NULL, "\n");
      return token;
    }
  }

  return NULL;
}

//
// App entry point
//
int main()
{
  const size_t len = 200;
  char buffer[len];

  FILE *fp = fopen("/proc/cpuinfo", "r");
  if (fp) {
    while (!feof(fp) &&  !ferror(fp)) {
      fread(buffer, sizeof(char), len, fp);

      // Get line # cpu MHz
      char *clock = find_cpu_clock(buffer);
      if (clock != NULL) {
        printf("Cpu Clock (MHz): %s\n", clock);
        break;
      }
    }

    fclose(fp);
  }

  return 0;
}
