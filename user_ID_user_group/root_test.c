#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("pid: %d-->ruid is %d, euid is %d \n", getpid(), getuid(), geteuid());
    printf("pid: %d-->rgid is %d, egid is %d \n", getpid(), getgid(), getegid());
    return 0;
}