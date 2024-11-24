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
    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        while ((line = get_next_line(fd)))
        {
            printf("%s\n", line);
            // free(line);
        }
        close(fd);
    }
    return (0);
}