// Listing 2.9 (tifftest.c) Using libtiff
// NOTE: libtiff is too old so going to use libpng

#include <stdio.h>
#include <stdlib.h>
#include <png.h>

/* Convert PNG interlace into string */
static const char* str_interlace(png_byte val)
{
  switch(val) {
    case PNG_INTERLACE_NONE:    return "None";      break;
    case PNG_INTERLACE_ADAM7:   return "Adam7";     break;
    case PNG_INTERLACE_LAST:    return "Invalid";   break;
    default:                    return "Unknown";   break;
  }
}

/* Convert PNG color type into string */
static const char* str_color_type(png_byte val)
{
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
static const char* str_channels(png_byte val)
{
  switch(val) {
    case 1:     return "Gray/Palette";  break;
    case 2:     return "Gray_Alpha";    break;
    case 3:     return "RGB";           break;
    case 4:     return "RGB_Alpha";     break;
    default:    return "Unknown";       break;
  }
}

//
// App entry point
//
int main(int argc, char* argv[])
{

  if (argc != 2) {
    printf("%s </path/to/png/file>\n", argv[0]);
    return -1;
  }

  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    printf("Unable to open given file (%s)\n", argv[1]);
    return -1;
  }

  /* Read header */
  char header[8];
  fread(header, 1, 8, fp);

  /* Verify PNG header */
  int is_png = !png_sig_cmp((png_bytep)header, 0, 8);
  if(!is_png) {
    printf("Input file(%s) is not of png format\n", argv[1]);
    fclose(fp);
    return -1;
  }

  /* Create png read structure */
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    printf("Fail to create png read structure\n");
    fclose(fp);
    return -1;
  }

  /* Create png info structure */
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    printf("Fail to create png info structure\n");
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(fp);
    return -1;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_info_struct(png_ptr, &info_ptr);
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(fp);
    return -1;
  }

  /* Initialize PNG IO */
  png_init_io(png_ptr, fp);

  /* We have already read 8 bytes for format verification so ignore those */
  png_set_sig_bytes(png_ptr, 8);

  /* Read png info  */
  png_read_info(png_ptr, info_ptr);

  /* Extract metadata of the image */
  const char *version = png_get_libpng_ver(png_ptr);
  png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
  png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
  png_byte interlace = png_get_interlace_type(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte channels = png_get_channels(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  printf("libpng version: %s\n", version);
  printf("Width:          %u\n", width);
  printf("Height:         %u\n", height);
  printf("Interlace type: %d:%s\n", interlace, str_interlace(interlace));
  printf("Color Type:     %d:%s\n", color_type, str_color_type(color_type));
  printf("Channels:       %d:%s\n", channels, str_channels(channels));
  printf("Bit Depth:      %d\n", bit_depth);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_read_struct(&png_ptr, NULL, NULL);
  fclose(fp);

  return 0;
}
