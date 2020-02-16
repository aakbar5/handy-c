// Listing 2.7 (test.c) Library Contents
// Listing 2.8 (app.c) A Program That Uses Library Functions

#include <stdio.h>

// available in test.c
extern int test_lib_func(int number);

//
// App entry point
//
int main() {
    int number = 100;
    printf("Input Number:  %d\n", number);
    printf("Call Test lib: %d\n", test_lib_func(number));
    return 0;
}