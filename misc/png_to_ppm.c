/**
 * Program
 *  This program converts a PNG file to PPM format.
 *
 * Compile
 *  gcc -Wall -Wextra png_to_ppm.c -o png_to_ppm -lpng
 *
 * Execution
 *  ./png_to_ppm --input test.png --output test.ppm
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
      "      -i | --input    Source png image\n"
      "      -o | --output   Output PPM image\n"
      "\n",
      argv[0]
  );

  (void)argc;
}

/* Convert PNG interlace into string */
const char* str_interlace(png_byte val) {
  switch(val) {
    case PNG_INTERLACE_NONE:    return "None";      break;
    case PNG_INTERLACE_ADAM7:   return "Adam7";     break;
    case PNG_INTERLACE_LAST:    return "Invalid";   break;
    default:                    return "Unknown";   break;
  }
}

/* Convert PNG color type into string */
const char* str_color_type(png_byte val) {
  switch(val) {
    case PNG_COLOR_TYPE_GRAY:           return "Gray";          break;
    case PNG_COLOR_TYPE_PALETTE:        return "Palette";       break;
    case PNG_COLOR_TYPE_RGB:            return "RGB";           break;
    case PNG_COLOR_TYPE_RGB_ALPHA:      return "RGB_Alpha";     break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:     return "Gray_Alpha";    break;
    default:                            return "Unknown";       break;
  }
}

/* Convert PNG channel into string */
const char* str_channels(png_byte val) {
  switch(val) {
    case 1:     return "Gray/Palette";  break;
    case 2:     return "Gray_Alpha";    break;
    case 3:     return "RGB";           break;
    case 4:     return "RGB_Alpha";     break;
    default:    return "Unknown";       break;
  }
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

  char header[8];

  printf("Convert PNG file to PPM\n");

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

  /* Read 8bytes for header */
  fread(header, 1, 8, fip);

  /* Verify PNG header */
  int is_png = !png_sig_cmp((png_bytep)header, 0, 8);
  if(!is_png) {
    printf("Input file(%s) is not of png format\n", input);
    err = -1;
    goto error1;
  }

  /* Create png read structure */
  /* Passing NULL to use the libpng provided error handling routines */
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    printf("Fail to create png read structure\n");
    err = -1;
    goto error1;
  }

  /* Create png info structure */
  png_infop png_info_ptr = png_create_info_struct(png_ptr);
  if (!png_info_ptr) {
    printf("Fail to create png info structure\n");
    err = -1;
    goto error2;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    err = -1;
    goto error3;
  }

  /* Initialize PNG IO */
  png_init_io(png_ptr, fip);

  /* We have already read 8 bytes for format verification so ignore those */
  png_set_sig_bytes(png_ptr, 8);

  /* Read png info  */
  png_read_info(png_ptr, png_info_ptr);

  png_uint_32 x, y;

  /* Extract metadata of the image */
  char *version = png_get_libpng_ver(png_ptr);
  png_uint_32 width = png_get_image_width(png_ptr, png_info_ptr);
  png_uint_32 height = png_get_image_height(png_ptr, png_info_ptr);
  png_byte interlace = png_get_interlace_type(png_ptr, png_info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, png_info_ptr);
  png_byte channels = png_get_channels(png_ptr, png_info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, png_info_ptr);

  printf("libpng version: %s\n", version);
  printf("Width:          %ld\n", width);
  printf("Height:         %ld\n", height);
  printf("Interlace type: %d:%s\n", interlace, str_interlace(interlace));
  printf("Color Type:     %d:%s\n", color_type, str_color_type(color_type));
  printf("Channels:       %d:%s\n", channels, str_channels(channels));
  printf("Bit Depth:      %d\n", bit_depth);

  /* Apply transformation to get regular RGB triplets */
  if (bit_depth == 16) {
    png_set_strip_16(png_ptr);
  }

  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png_ptr);
  }

  /* PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth */
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
    png_set_expand_gray_1_2_4_to_8(png_ptr);
  }

  if (png_get_valid(png_ptr, png_info_ptr, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png_ptr);
  }

  /* These color_type don't have an alpha channel then fill it with 0xff */
  if (color_type == PNG_COLOR_TYPE_RGB  ||
    color_type == PNG_COLOR_TYPE_GRAY ||
    color_type == PNG_COLOR_TYPE_PALETTE) {
    png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
  }

  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
    png_set_gray_to_rgb(png_ptr);
  }

  /* Update PNG info */
  png_read_update_info(png_ptr, png_info_ptr);

  /* Get bytes required to hold one row */
  png_uint_32 rowbytes = png_get_rowbytes(png_ptr, png_info_ptr);

  /* Allocate memory for png rows */
  png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
  if (row_pointers == NULL) {
    printf("Fail to allocate memory\n");
    err = -1;
    goto error3;
  }

  for (y = 0; y < height; ++y) {
    row_pointers[y] = (png_bytep) malloc(rowbytes);
    if (row_pointers[y] == NULL) {
      printf("Fail to allocate memory\n");
      err = -1;
      goto error4;
    }
  }

  /* Read image data */
  png_read_image(png_ptr, row_pointers);

  /* Write output file */
  FILE *fop = fopen(output, "w+");
  if (!fop) {
    printf("Unable to open output file(%s)\n", output);
    err = -1;
    goto error4;
  }

  /* Write PPM header */
  fprintf(fop, "P6\n");
  fprintf(fop, "# PNG to PPM\n");
  fprintf(fop, "%ld %ld\n", width, height);
  fprintf(fop, "255\n");

  for (y = 0; y < height; y++) {
    png_bytep rowp = row_pointers[y];
    for (x = 0; x < width; x++) {
      png_byte pixel_r = rowp[x * 4 + 0];
      png_byte pixel_g = rowp[x * 4 + 1];
      png_byte pixel_b = rowp[x * 4 + 2];
      /* png_byte pixel_a = rowp[x * 4 + 3]; */
      fprintf(fop, "%c%c%c", pixel_r, pixel_g, pixel_b);
    }
  }

  fclose(fop);

error4:
  for (y = 0; y < height; ++y) {
    if (row_pointers[y])
      free(row_pointers[y]);
  }

  free(row_pointers);

error3:
  png_destroy_info_struct(png_ptr, &png_info_ptr);

error2:
  png_destroy_read_struct(&png_ptr, NULL, NULL);

error1:
  fclose(fip);

  printf("Good bye!\n");
  return err;
}
