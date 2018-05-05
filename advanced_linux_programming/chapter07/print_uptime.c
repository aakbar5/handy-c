// Listing 7.7 (print-uptime.c) Print the System Uptime and Idle Time

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Handy function to format time value
char* format(double value)
{
  const int len = 256;
  const int seconds_in_hours = 60 * 60;
  const int seconds_in_day = 24 * seconds_in_hours;

  char *string = malloc(len);
  if (!string)
    return NULL;

  string[0] = '\0';
  if (value > seconds_in_day) {
    int days = value / seconds_in_day;
    value -= days * seconds_in_day;
    sprintf(string, "%d days ", days);
  }

  if (value > seconds_in_hours) {
    int hours = value / seconds_in_hours;
    value -= hours * seconds_in_hours;
    sprintf(string + strlen(string), "%d hours ", hours);
  }

  if (value > 60) {
    int minutes = value / 60;
    value -= minutes * 60;

    sprintf(string + strlen(string), "%d mintues ", minutes);
  }

  sprintf(string + strlen(string), "%d seconds", (int)value);
  return string;
}

//
// App entry point
//
int main()
{
  double uptime, idletime;

  FILE *fp = fopen("/proc/uptime", "r");
  if (fp) {
    fscanf(fp, "%lf %lf\n", &uptime, &idletime);
    fclose(fp);
  }

  char *str = format(uptime);
  printf("Up time:   %lf (%s)\n", uptime, str);
  free(str);

  str = format(idletime);
  printf("Idle time: %lf (%s)\n", idletime, format(idletime));
  free(str);

  return 0;
}
