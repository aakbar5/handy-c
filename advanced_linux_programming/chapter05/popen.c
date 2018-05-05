// Listing 5.9 (popen.c) Example Using popen

#include <stdio.h>
#include <unistd.h>

//
// App entry point
//
int main()
{
    FILE *fp = popen("sort", "w");
    fprintf(fp, "1 - Hello world!\n");
    fprintf(fp, "8 - Hello world!\n");
    fprintf(fp, "3 - Hello world!\n");
    fprintf(fp, "2 - Hello world!\n");
    fflush(fp);
    pclose(fp);

    return 0;
}
