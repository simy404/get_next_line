//test get_next_line.c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void putstr(char* str)
{   
    if(!str)
    {
        write (1, "(NULL)", 6);
        return ;
    }
        while(*str)
    {
        if (*str == '\n')
            write(1, "\\n", 2);
        else
            write(1, str, 1);
        str++;
    }
}

int main(int ac, char **av)
{
    int fd;
    char *line;
    int i = 0;

    fd = open("test2", O_RDONLY);
    int overflow = 3;
    do {
        line = get_next_line(fd);
        printf("%s", line);
        //printf("adress: %p\n", line);
        free(line);
        i++;
    } while (/*line != NULL && */ overflow--);
    close(fd);
    return (0);
}
