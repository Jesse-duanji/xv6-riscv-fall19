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
        //parent process
        for (int i = 3; i <= 35; i++)
        {
            if (i % 2 != 0)
            {
                write(fd[0],&i,4);
            }
        }
    }
    else if (pid == 0)
    {
        //child process
        int res;
        read(fd[1],&res,4);
        printf("read process %d",res);
    }
    exit();
}