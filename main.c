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

    do {
        line = get_next_line(fd);
        if(!line)
            break;
        printf("%s", line);
        //printf("adress: %p\n", line);
        free(line);
        i++;
    } while (line != NULL);
    close(fd);
    return (0);
}
