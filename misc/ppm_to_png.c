/**
 * Program
 *  This program converts a PPM file to PPM format.
 *
 * Compile
 *  gcc -Wall -Wextra ppm_to_png.c -o ppm_to_png -lpng
 *
 * Execution
 *  ./ppm_to_png --input test.ppm --output output.png
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* #define PNG_DEBUG 3 */
#include <png.h>

static const char short_options[] = "hi:o:";
static const struct option long_options[] =
{
  { "help",       no_argument,        NULL, 'h' },
  { "input",      required_argument,  NULL, 'i' },
  { "output",     required_argument,  NULL, 'o' },
  { 0, 0, 0, 0 }
};

/* Show program usage */
static void usage(int argc, char **argv)
{
  printf(
      "\n"
      "Usage: %s [options]\n"
      "      Options:\n"
      "      -h | --help     Show help message\n"
      "      -i | --input    Source PPM image\n"
      "      -o | --output   Output PNG image\n"
      "\n",
      argv[0]
  );

  (void)argc;
}

/**
 * Entry function
 */
int main(int argc, char *argv[])
{
  int err = 0;
  int opt;
  int option_index;

  char *input;
  char *output;

  printf("Convert PPM file to PNG\n");

  for (;;) {
    opt = getopt_long(argc, argv, short_options, long_options, &option_index);

    if (opt == -1)
      break;

    switch (opt) {
    case 'i':
      input = optarg;
    break;

    case 'o':
      output = optarg;
    break;

    case 'h':
    default:
      usage(argc, argv);
      exit(EXIT_FAILURE);
    break;
    }
  }

  printf("Input file: %s\n", input);
  printf("Output file: %s\n", output);

  /* Open file */
  FILE *fip = fopen(input, "rb");
  if (!fip) {
    printf("Unable to open input file(%s)\n", input);
    return -1;
  }

  char str[80];
  fgets(str, 80, fip);
  if (str[0] != 'P' || str[1] != '6') {
    printf("PPM format is not found\n");
    err = -1;
    goto error1;
  }

  int width = 0, height = 0;

  /* Read comment */
  while (1) {
    fgets(str, 80, fip);
    if (str[0] == '#') {
      /* Ignore it */
    }
    else {
      /* Tokenize it to extract resolution */

      char *pch = strtok(str, " ");
      if (pch) {
        width = atoi(pch);

        pch = strtok(NULL, " ");
        if (pch)
          height = atoi(pch);
      }

      printf("%dx%d\n", width, height);
      break;
    }
  }

  /* Get max color */
  fgets(str, 80, fip);

  int x, y;
  char r, g, b;

  /* Allocate memory for PNG rows */
  png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
  if (row_pointers == NULL) {
    printf("Fail to allocate memory\n");
    err = -1;
    goto error1;
  }

  for (y = 0; y < height; ++y) {
    row_pointers[y] = (png_bytep) malloc(sizeof(png_byte) * 4 * width);
    if (row_pointers[y] == NULL) {
      printf("Fail to allocate memory\n");
      err = -1;
      goto error2;
    }
  }

  for (y = 0; y < height; ++y) {
    png_bytep rowp = row_pointers[y];
    for (x = 0; x < width; ++x) {

      /* Read RGB from PPM */
      fscanf(fip, "%c%c%c", &r, &g, &b);

      /* Prepare buffer for PNG */
      rowp[x * 4 + 0] = r;
      rowp[x * 4 + 1] = g;
      rowp[x * 4 + 2] = b;
      rowp[x * 4 + 3] = 0xFF;
    }
  }

  /* Create file */
  FILE *fop = fopen(output, "wb");
  if(!fop) {
    printf("Fail to open file (%s)\n", output);
    err = -1;
    goto error2;
  }

  /* Write PNG structure */
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    printf("Fail to create png structure\n");
    err = -1;
    goto error3;
  }

  png_infop png_info_ptr = png_create_info_struct(png_ptr);
  if (!png_info_ptr) {
    printf("Fail to create info structure\n");
    err = -1;
    goto error3;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    printf("Fail to set png jmp\n");
    err = -1;
    goto error3;
  }

  png_init_io(png_ptr, fop);

  /* Format: RGBA format, Bit Depth:8 */
  png_set_IHDR(
    png_ptr,
    png_info_ptr,
    width, height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );

  /* Write PNG info and data */
  png_write_info(png_ptr, png_info_ptr);
  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, NULL);

error3:
  fclose(fop);

error2:
  for (y = 0; y < height; ++y) {
    if (row_pointers[y])
      free(row_pointers[y]);
  }

  if (row_pointers)
    free(row_pointers);

error1:
  fclose(fip);

  printf("Good bye!\n");
  return err;
}
