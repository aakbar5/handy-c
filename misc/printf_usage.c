/**
 * Program
 *  Printf with different options.
 *
 * Compile
 *  gcc -Wall -Wextra printf_usage.c -o printf_usage
 *
 * Execution
 *  ./printf_usage
 **/

#include <stdio.h>

/**
 * Entry function
 */
int main ()
{
  int a = 0;
  int *ptr = &a;

  // %[parameter][flags][width][.precision][length]type
  // Flags: - (left align), + (Append + sign), 0 (fill width with space)
  // #
  //  - For g and G types, trailing zeros are not removed.
  //  - For f, F, e, E, g, G types, the output always contains a decimal point.
  //  - For o, x, X types, the text 0, 0x, 0X, respectively, is preappend to non-zero numbers.

  printf("Showing different values:\n");
  printf("Show percent            %%\n");             // Show % sign
  printf("Character               %c\n", 'A');        // Show a character
  printf("String                  %s\n", "string");   // Show a NULL terminated string
  printf("Signed integer          %d\n", 100);        // Show signed decimal integer
  printf("Signed integer          %d\n", -100);       // Show signed decimal integer
  printf("Unsigned integer        %u\n", 100);        // Show unsigned decimal integer
  printf("Octal                   %o\n", 020);        // Show octal number
  printf("Hexadecimal (lower)     0x%x\n", 0xAA);     // Show hexadecimal integer (lowercase)
  printf("Hexadecimal (upper)     0x%X\n", 0xAA);     // Show hexadecimal integer (Uppercase)
  printf("Hexadecimal (8)         0x%08X\n", 0xAA);   // Show hexadecimal integer (Fill with zero)
  printf("Decimal float (f)       %f\n", 3.1415f);    // Show decimal floating point
  printf("Decimal float (F)       %F\n", 3.1415f);    // Show decimal floating point
  printf("Pointer                 %p\n", ptr);        // Show pointer
  printf("Scientific notation     %g\n", 10000000.0); // Use the shortest representation: %e or %f
  printf("Scientific notation     %G\n", 10000000.0); // Use the shortest representation: %E or %F

  printf("\nFloating point:\n");
  printf("    f        %f\n", 3.1415f);
  printf("  .1f        %.1f\n", 3.1415f);     // 1 number from mantissa
  printf("  .2f        %.2f\n", 3.1415f);     // 2 numbers from mantissa
  printf("  .*f        %.*f\n", 2, 3.1415f);  // 2 numbers from mantissa however precision control is itself a number
  printf(" 2.2f        %2.2f\n", 3.1415f);    // 2 number wide, two numbers from mantissa
  printf("06.2f        %06.2f\n", 3.1415f);   // 6 number wide, two numbers from mantissa, fill with 0
  printf(" 6.2f        %6.2f\n", 3.1415f);    // 6 number wide, two numbers from mantissa
  printf(" 6.2f        %-6.2f\n", 3.1415f);   // 6 number wide, two numbers from mantissa

  float f1 = +3.1415f;
  float f2 = -3.1415f;
  printf("Width +ve sign:  % 3.4f\n", f1);    // Make a note of space after %
  printf("Width -ve sign:  % 3.4f\n", f2);    // Make a note of space after %

  // Control minimum width
  printf("\nControl minimum width:\n");
  printf("Minimum Width: %5d\n", 10);
  printf("Minimum Width: %5c\n", 'A');
  printf("Minimum Width: %5s\n", "tes");

  printf("\nControl minimum width & alignment:\n");
  printf("Minimum Width (Right align): %5d\n", 10);
  printf("Minimum Width (Left align) : %-5d\n", 10);
  printf("Minimum Width (Right align): %5c\n", 'A');
  printf("Minimum Width (Left align) : %-5c\n", 'A');
  printf("Minimum Width (Right align): %5s\n", "tes");
  printf("Minimum Width (Left align) : %-5s\n", "tes");

  printf("\nControl minimum width & fill it:\n");
  printf("Minimum Width: %05d\n", 10);
  // printf("Minimum Width: %05c\n", 'A');   // Does not work as filling is for integer value
  // printf("Minimum Width: %05s\n", "tes"); // Doe not work as filling is for integer value

  // using flag #
  printf("\nUsing flag #\n");
  printf("Hexadecimal    :  %x\n",  10);  // Show respective hexadecimal
  printf("Hexadecimal (#):  %#x\n", 10);  // Preappend 0x to hexadecimal
  printf("Octal          :  %o\n",  10);  // Show respective octal
  printf("Octal (#)      :  %#o\n", 10);  // Preappend 0 to octal

  // Show Hexadecimal of 10; use width of 10; fill space with 10
  printf("Showing memory value:  %#010x\n", 10);

  return 0;
}
