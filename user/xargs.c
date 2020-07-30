#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char buf[512];
    char *c = 0;
    int i = 0; // current cursor
    while (read(0, c, 1) > 0)
    {
        if (i < sizeof(buf) - 1) // remain the last position for '\n'
        {
            if (*c != '\n')
            {
                buf[i++] = *c;
            }
            else
            {
                buf[i] = '\0';
                printf("line is %s", buf);
            }
        }
        else
        {
            fprintf(2, "size of line is too long!");
            return -1;
        }
    }
    exit();
}