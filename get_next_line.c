/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jneris-d <tbpjaum@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by jneris-d          #+#    #+#             */
/*   Updated: 0000/00/00 00:00:00 by jneris-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char *lastbuffer;
    static int  i;
    char    *buffer[BUFFER_SIZE + 1];
    char    *line[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    int     j;

    if (!i)
        i = 0;
    j = 0;
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (NULL);
    buffer[bytes_read] = '\0';

    if (!lastbuffer)
        lastbuffer = strdup(buffer);
    else
    {
        char *temp;
        temp = malloc(strlen(lastbuffer) + bytes_read + 1);
        strcpy(temp, lastbuffer);
        strcat(temp, buffer);
        free(lastbuffer);
        lastbuffer = temp;
    }
    while (lastbuffer[i] != '\0' && lastbuffer[i] != '\n')
    {
        line[i] = lastbuffer[i];
        i++;
    }
    if (lastbuffer == '\0')
        return (line);
    else if (lastbuffer == '\n')
        line[i] = '\n';
    else
        get_next_line(fd);
    return (line);
}
