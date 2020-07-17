#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/**
 * Write a program that uses UNIX system calls to ``ping-pong'' 
 * a byte between two processes over a pair of pipes, 
 * one for each direction. The parent sends by writing a byte 
 * to parent_fd[1] and the child receives it by reading from 
 * parent_fd[0]. After receiving a byte from parent, 
 * the child responds with its own byte by writing to child_fd[1], 
 * which the parent then reads. 
 * Your solution should be in the file user/pingpong.c.
 */
int main(int argc,char *argv[]){
    int parent_fd[2];
    int child_fd[2];
    pipe(parent_fd);
    pipe(child_fd);

    int pid=fork();
    if(pid>0){
        //parent pid
        close(parent_fd[0]);
        close(child_fd[1]);
        char buf[1]={0};
        write(parent_fd[1],buf,1);
        read(child_fd[0],buf,1);
        printf("%d: received pong\n",getpid());
    }else if(pid==0){
        //child pid
        close(parent_fd[1]);
        close(child_fd[0]);
        char buf[1]={0};
        read(parent_fd[0],buf,1);
        printf("%d: received ping\n",getpid());
        write(child_fd[1],buf,1);
    }
    exit();
}