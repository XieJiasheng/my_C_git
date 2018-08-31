#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fd1, fd2;
    fd1 = open(argv[0], O_RDONLY);
    fd2 = open(argv[1], O_RDWR);
    printf("%s:fd is %d, %s:fd is %d\n", argv[0], fd1, argv[1], fd2);
    pause();
    return 0;
}