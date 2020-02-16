// Listing 8.13 (print-uname) Print Linux Version Number and
// Hardware Information

#include <stdio.h>
#include <sys/utsname.h>

//
// App entry point
//
int main()
{
    struct utsname uinfo;
    uname(&uinfo);
    printf("%s release %s (version %s) on %s\n",
                uinfo.sysname,
                uinfo.release,
                uinfo.version,
                uinfo.machine);
    return 0;
}
