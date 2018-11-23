#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>


int main(int argc, char const *argv[])
{
    int status;
    pid_t pid;



    printf("pid: %d-->ruid is %d, euid is %d \n", getpid(), getuid(), geteuid());
    printf("pid: %d-->rgid is %d, egid is %d \n", getpid(), getgid(), getegid());

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if (!pid)
    {
        printf("pid: %d-->ruid is %d, euid is %d \n", getpid(), getuid(), geteuid());
        printf("pid: %d-->rgid is %d, egid is %d \n", getpid(), getgid(), getegid());
        char * const args[] = {"root_test", "-l", NULL};
        int ret;
        ret = execv("root_test", args);
        if (ret == -1)
        {
            perror("execv");
            exit(EXIT_FAILURE);
        }
        printf("pid: %d-->ruid is %d, euid is %d \n", getpid(), getuid(), geteuid());
        printf("pid: %d-->rgid is %d, egid is %d \n", getpid(), getgid(), getegid());
    }
    else
    {
        pid = wait(&status);
        if (pid == -1)
        {
            perror("wait");
        }
        printf("pid: %d-->ruid is %d, euid is %d \n", getpid(), getuid(), geteuid());
        printf("pid: %d-->rgid is %d, egid is %d \n", getpid(), getgid(), getegid());
    
    }
    printf("pid: %d-->ruid is %d, euid is %d \n", getpid(), getuid(), geteuid());
    printf("pid: %d-->rgid is %d, egid is %d \n", getpid(), getgid(), getegid());
    

    return 0;
}