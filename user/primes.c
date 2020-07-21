#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    close(fd[0]);
    for (int i = 2; i <= 35; i++)
    {
        write(fd[1], &i, 4);
    }
    handle_data(fd);
    exit();
}

/**
 * handel data in pipeline
 */
void handle_data(int left_fd[2])
{
    close(left_fd[1]); // close write end
    int prime;
    int prime_read_res=read(left_fd[0], &prime, 4);
    if(prime_read_res<0){
        return;
    }
    printf("prime %d\n", prime);

    int data;
    int read_res = read(left_fd[0], &data, 4);
    if (read_res > 0)
    {
        // has more data
        // fork a process to handle next prime
        int right_fd[2];
        pipe(right_fd);

        int pid = fork();
        if (pid > 0)
        {
            close(right_fd[0]); // close read end
            //parent
            do
            {
                if (data % prime != 0)
                {
                    //write to next process
                    write(right_fd[1], &data, 4);
                }
            } while (read_res = read(left_fd[0], &data, 4) > 0);
        }
        else if (pid == 0)
        {
            //child
            process(right_fd);
        }
    }
    else if (read_res == 0)
    {
        // no data, do nothing
    }
    else
    {
        printf("read data from pipe error!");
    }
}