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

char *get_line(int fd, char *leftover);

char    *get_next_line(int fd)
{
    static char *leftover = NULL;
    char        *next_line;

    if (fd < 0 || BUFFER_SIZE  <= 0)
        return (0);
    
    next_line = get_line()
    
    return NULL;
}
