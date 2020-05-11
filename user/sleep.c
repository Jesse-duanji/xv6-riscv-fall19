#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    if(argc != 2){
        // if the user forgets to pass an argument, print an error message
        printf("sleep error! one argument is needed\n");
        exit();
    }


}