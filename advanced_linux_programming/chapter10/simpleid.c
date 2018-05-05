// Listing 10.1 (simpleid.c) Print User and Group IDs

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
    gid_t rgid = getgid();
    gid_t egid = getegid();

    printf("User ID (real):       %d\n", ruid);
    printf("User ID (Effective):  %d\n", euid);
    printf("Group ID (real):      %d\n", rgid);
    printf("Group ID (Effective): %d\n", egid);

    return 0;
}
