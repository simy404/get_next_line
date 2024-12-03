/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:31:13 by hsamir            #+#    #+#             */
/*   Updated: 2024/12/01 15:31:17 by hsamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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

int	update_leftover(char **leftover)
{
	char	*newline_ptr;

	newline_ptr = ft_strchr(*leftover, '\n');
	if (newline_ptr && newline_ptr[1] != '\0')
	{
		*leftover = ft_strdup(newline_ptr + 1);
		if (!(*leftover))
			return (1);
	}
	else
		*leftover = NULL;
	return (0);
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
	if (update_leftover(&leftover))
	{
		free(next_line);
		next_line = NULL;
	}
	free(temp);
	return (next_line);
}
