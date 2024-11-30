//test get_next_line.c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int fd;
    char *line;
    int i = 0;

    fd = open("test2", O_RDONLY);
    while ((i < 7))
    {
        line = get_next_line(fd);
        printf("%s\n", line);
        printf("adress: %p\n", line);
        free(line);
        i++;
    }
    close(fd);
    return (0);
}
