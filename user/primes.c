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
        close(fd[1]);
        //parent process
        for (int i = 3; i <= 35; i++)
        {
            if (i % 2 != 0)
            {
                printf("prepare to write:%d", i);
                write(fd[0], &i, 4);
            }
        }
        close(fd[0]);
    }
    else if (pid == 0)
    {
        //child process
        close(fd[0]);
        int res;
        while (read(fd[1], &res, 4) != 0)
        {
            printf("read process %d\n", res);
        }
    }
    exit();
}