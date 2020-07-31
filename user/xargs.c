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
            else if (*c == 04)
            {
                printf("ctrl + D pressed\n");
                break;
            }
            else
            {
                buf[i] = '\0';
                printf("line is %s\n", buf);

                //fork and execute command
                char *params[MAXARG];
                int paramIndex = 0;
                for (int i = 1; i < argc; i++)
                {
                    printf("%d param is %s\n", i, argv[i]);
                    params[paramIndex++] = argv[i];
                }

                //continue parse params
                char *paramBuf = malloc(sizeof(char) * 512);
                int paramBufIndex = 0;
                for (int i = 0; i < strlen(buf); i++)
                {
                    // printf("char %c",buf[i]);
                    if (buf[i] == ' ')
                    {
                        //new param end
                        paramBuf[paramBufIndex] = '\0';
                        params[paramIndex++] = paramBuf;
                        paramBuf = malloc(sizeof(char) * 512);
                        paramBufIndex = 0;
                    }
                    else
                    {
                        paramBuf[paramBufIndex++] = buf[i];
                    }
                }

                //start to execute command
                int pid = fork();
                if (pid > 0)
                {
                    wait();
                }
                else
                {
                    exec(params[0], params);
                }

                for (int i = 0; i < MAXARG; i++)
                {
                    if (params[i] != 0)
                    {
                        printf("param:%s\n", params[i]);
                    }
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