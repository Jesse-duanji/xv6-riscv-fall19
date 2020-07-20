#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid > 0)
    {
        printf("prime %d\n", 2);
        close(fd[0]);
        //parent process
        for (int i = 3; i <= 35; i++)
        {
            if (i % 2 != 0)
            {
                printf("prepare to write:%d\n", i);
                write(fd[1], &i, 4);
            }
        }
        close(fd[0]);
    }
    else if (pid == 0)
    {
        //child process
        close(fd[1]);
        int res;
        while (read(fd[0], &res, 4) > 0)
        {
            printf("read process %d\n", res);
        }
    }
    exit();
}