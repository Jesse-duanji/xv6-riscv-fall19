#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

void find(char *path, char *name)
{
    printf("find from path:%s", path);
    struct stat st;
    int fd;
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: can't open %s", path);
        close(fd);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: can't stat %s", path);
        close(fd);
        return;
    }
    printf("dev:%d info:%d type:%d nlink:%d size:%d",st.dev,st.ino,
        st.type,st.nlink,st.size);

    switch (st.type)
    {
    case T_FILE:
        // compare with name directly
        break;
    case T_DIR:
        //check file
        //find recursively
        break;
    }
    exit();
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("error params number");
        exit();
    }
    char *path = argv[1];
    char *name = argv[2];

    find(path, name);
}