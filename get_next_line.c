/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:48:10 by hsamir            #+#    #+#             */
/*   Updated: 2024/11/24 14:11:44 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *read_line(int fd, char *str)
{
    char *buffer;
    char *temp;
    int read_bytes;

    read_bytes = 1;
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while(read_bytes > 0 && !ft_strchr(str, '\n'))
    {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes == -1)
        {
            free(buffer); //TODO if read fails, what can i do with str ?
            return (NULL);
        }
        buffer[read_bytes] = '\0';
        temp = str; //TODO find a another way to free str
        str = ft_strjoin(str, buffer); //TODO if buffer is null, what can i do ?
            // printf("buffer: %s\n", buffer);
            // printf("merged str: %s\n", str);
        free(temp);
    }
    free(buffer);
    return (str);
}

char *get_line(char *str)
{
    int i;
    char *line;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    if (str[i] == '\n')
    {
        line[i] = str[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char* get_leftover(char *str)
{
    int i;
    int j;
    char *leftover;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (!str[i])
    {
        free(str);
        return (NULL);
    }
    leftover = malloc(ft_strlen(str) - i + 1); // test\ntest\n\0
    if (!leftover)
        return (NULL);
    i++;
    j = 0;
    while (str[i])
    {
        leftover[j] = str[i];
        i++;
        j++;
    }
    leftover[j] = '\0';
    free(str);
    return (leftover);
}

char    *get_next_line(int fd)
{
    static char *leftover = NULL;
    char        *next_line;

    if (fd < 0 || BUFFER_SIZE  <= 0 || read(fd, NULL, 0) == -1) //TODO do i have to check -1 ?
        return (0);
    leftover = read_line(fd, leftover);
    if (!leftover)
        return (NULL);
    next_line = get_line(leftover);
    leftover = get_leftover(leftover);
    // printf("leftover: %s\n", leftover);

    return (next_line);
}
