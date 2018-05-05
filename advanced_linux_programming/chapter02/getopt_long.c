// Listing 2.2 (getopt_long.c) Using getopt_long

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define DEFAULT_OPTION1     1
#define DEFAULT_OPTION2     2
#define DEFAULT_OPTION3     3

static const char short_options[] = "ho:p:t:";
static const struct option long_options[] =
{
  { "help",       no_argument,        NULL, 'h' },
  { "option1",    required_argument,  NULL, 'o' },
  { "option2",    required_argument,  NULL, 'p' },
  { "option3",    required_argument,  NULL, 't' },
  { 0, 0, 0, 0 }
};

// Handy function to show usage
static void usage(FILE *fp, int argc, char **argv)
{
  fprintf(fp,
     "Usage: %s [options]\n"
     "      Options:\n"
     "      -h | --help     Show help message\n"
     "      -o | --option1  This is option # 1(%d)\n"
     "      -p | --option2  This is option # 2(%d)\n"
     "      -t | --option3  This is option # 3(%d)\n"
     "",
     argv[0],
     DEFAULT_OPTION1,
     DEFAULT_OPTION2,
     DEFAULT_OPTION3
  );

  (void)argc;
}

//
// App entry point
//
int main(int argc, char* argv[])
{
  int option1 = DEFAULT_OPTION1;
  int option2 = DEFAULT_OPTION2;
  int option3 = DEFAULT_OPTION3;

  int option_index;
  int opt;

  for (;;) {
    opt = getopt_long(argc, argv, short_options, long_options, &option_index);

    // All user passed arguments have been parsed
    if (opt == -1)
      break;

    switch (opt)
    {
    case 0:
      printf("=== having zero ===");
    break;

    case 'o':
      option1 = atoi(optarg);
    break;

    case 'p':
      option2 = atoi(optarg);
    break;

    case 't':
      option3 = atoi(optarg);
    break;

    case 'h':
    default:
      usage(stderr, argc, argv);
      exit(EXIT_FAILURE);
    break;
    }
  }

  printf("-----------------------------------\n");
  printf("getopt_long -- parsed options: \n");
  printf("option # 1: %d\n", option1);
  printf("option # 2: %d\n", option2);
  printf("option # 3: %d\n", option3);
  printf("-----------------------------------\n");

  return 0;
}
