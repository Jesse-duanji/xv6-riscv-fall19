#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
#include <kernel/fs.h>

void find(char *path, char *name)
{
    printf("find from path:%s\n", path);
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
    printf("dev:%d info:%d type:%d nlink:%d size:%d\n", st.dev, st.ino,
           st.type, st.nlink, st.size);

    struct dirent de;
    switch (st.type)
    {
    case T_FILE:
    {
        printf("%s is a file\n",path);
        // compare with name directly
        char *p;
        for (p = path + strlen(path); p >= path && *p != '/'; p--)
            ;
        p++; //find first character after last slash

        printf("p is %s name is %s",p,name);

        if (strcmp(p, name) == 0)
        {
            //equals
            printf("%s\n", path);
        }
    }
    break;
    case T_DIR:
        //check file
        printf("%s is a directory",path);
        if (strcmp(".", path) == 0 || strcmp("..", path) == 0)
        {
            printf("not recurse into . and ..\n");
            return;
        }
        char buf[512];
        //find recursively
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            printf("inum:%d name:%s \n", de.inum, de.name);
            // 拼接path，然后递归find
            strcpy(buf,path);
            char *p = buf + strlen(buf);
            p++;
            *p = "/";
            memmove(p, de.name, DIRSIZ);
            printf("append file name:%s",buf);
        }
        break;
    }
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
    exit();
}