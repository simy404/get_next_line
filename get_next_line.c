/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:48:10 by hsamir            #+#    #+#             */
/*   Updated: 2024/11/30 18:49:15 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *read_line(int fd, char *str)
{
    char	buffer[BUFFER_SIZE + 1];
    char	*temp;
    int		read_bytes;

    read_bytes = 1;
    while (read_bytes > 0 && !ft_strchr(str, '\n'))
    {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!read_bytes)
			break;
        if (read_bytes == -1)
        {
            free(str);
            return (NULL);
        }
        buffer[read_bytes] = '\0';
        temp = str; //TODO find a another way to free str
        str = ft_strjoin(str, buffer); //TODO if buffer is null, what can i do ?
        free(temp);
    }
    return (str);
}

char *get_line(char *str)
{
    int i;
    char *line;

	line = ft_strchr(str, '\n');
	if (!line)
		return (ft_strdup(str));
	i = line - str;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, str, i + 1);
	line[i + 1] = '\0';
	return (line);
}

char* get_leftover(char *str)
{
    int i;
    int j;
    char *leftover;

	leftover = ft_strchr(str, '\n');
	if (!leftover)
		return (NULL); //TODO i have to check it -------            ab\n\0
    i = leftover - str;
	printf("i: %d\nstr - i = %ld \n", i ,(ft_strlen(str) - i));
	if (!i)
		return (0);
	leftover = malloc(ft_strlen(str) - i);
	if (!leftover)
		return (NULL);
	ft_memcpy(leftover, &str[i + 1] ,(ft_strlen(str) - i - 1));
	leftover[ft_strlen(str) - i - 1] = 0;
	return (leftover);
}

char    *get_next_line(int fd)
{
    static char *leftover = NULL;
    char        *next_line = NULL;
	char 	  *temp;

    if (fd < 0 || BUFFER_SIZE  <= 0) //|| read(fd, NULL, 0) == -1) //TODO do i have to check -1 ?
        return (0);
    leftover = read_line(fd, leftover);
    if (!leftover)
        return (NULL);
	next_line = get_line(leftover);
	temp = leftover;
    leftover = get_leftover(leftover);
	free(temp);
    return (next_line);
}
