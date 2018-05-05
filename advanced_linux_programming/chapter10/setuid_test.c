// Listing 10.3 (setuid-test.c) Setuid Demonstration Program

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

//
// App entry point
//
int main()
{
    uid_t ruid = getuid();
    uid_t euid = geteuid();

    printf("User ID (real):       %d\n", ruid);
    printf("User ID (Effective):  %d\n", euid);

    return 0;
}
