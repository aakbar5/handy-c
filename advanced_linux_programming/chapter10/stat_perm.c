// Listing 10.2 (stat-perm.c) Determine File Owner’s Write Permission

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

//
// App entry point
//
int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: Pass file name to stat\n");
        exit(0);
    }

    struct stat buf;
    const char* const filename = argv[1];
    stat(filename, &buf);
    if (buf.st_mode & S_IWUSR)
        printf ("File can be written\n");

    return 0;
}
