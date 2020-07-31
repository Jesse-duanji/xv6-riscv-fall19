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
                printf("line is %s\n", buf);

                //fork and execute command
                char *params[MAXARG];
                for (int i = 1; i < sizeof(argv); i++)
                {
                    printf("%d param is %s\n", i, argv[i]);
                }

                i = 0;
            }
        }
        else
        {
            fprintf(2, "size of line is too long!\n");
            return -1;
        }
    }
    exit();
}