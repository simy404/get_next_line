/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:48:10 by hsamir            #+#    #+#             */
/*   Updated: 2024/12/01 11:04:58 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*fill_buffer(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		read_bytes;

	read_bytes = BUFFER_SIZE;
	while (read_bytes == BUFFER_SIZE && (!str || !ft_strchr(str, '\n')))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes == -1)
		{
			free(str);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = str;
		str = ft_strjoin(str, buffer);
		free(temp);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_part_until_nl(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, str, i);
	line[i] = 0;
	return (line);
}

char	*get_leftover(char *str)
{
	char	*newline_ptr;

	if (str)
	{
		newline_ptr = ft_strchr(str, '\n');
		if (newline_ptr)
		{
			if (newline_ptr[1] != '\0')
				return (ft_strdup(newline_ptr + 1));
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*next_line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = fill_buffer(fd, leftover);
	if (!leftover)
		return (NULL);
	next_line = get_part_until_nl(leftover);
	if (!next_line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	temp = leftover;
	leftover = get_leftover(leftover);
	free(temp);
	return (next_line);
}
