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

void	*ft_handle_error(char **buffer, char **lastbuffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (lastbuffer && *lastbuffer)
	{
		free(*lastbuffer);
		*lastbuffer = NULL;
	}
	return (NULL);
}

char	*ft_cat_n_check(char *lastbuffer, char *buffer)
{
	char	*temp;

	if (!lastbuffer)
		return (ft_substr(buffer, 0, ft_strlen(buffer)));
	temp = malloc(ft_strlen(lastbuffer) + ft_strlen(buffer) + 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, lastbuffer);
	ft_strcat(temp, buffer);
	free(lastbuffer);
	return (temp);
}

void	*ft_check(int fd, char **lastbuffer, char **buffer, ssize_t *bytes_read)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*buffer = malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (NULL);
	if (!*lastbuffer)
	{
		*bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (*bytes_read <= 0)
			return (ft_handle_error(buffer, NULL));
		(*buffer)[*bytes_read] = '\0';
		*lastbuffer = ft_substr(*buffer, 0, *bytes_read);
		if (!*lastbuffer)
			return (ft_handle_error(buffer, NULL));
	}
	return (lastbuffer);
}

char	*ft_return_next_line(char *newline_pos, char **lastbuffer)
{
	char	*tmp;
	char	*line;
	size_t	line_length;
	size_t	total_len;

	if (newline_pos)
	{
		line_length = newline_pos - *lastbuffer + 1;
		line = ft_substr(*lastbuffer, 0, line_length);
		if (!line)
		{
			free (*lastbuffer);
			return (NULL);
		}
		total_len = ft_strlen(*lastbuffer) - line_length;
		tmp = ft_substr(*lastbuffer, line_length, total_len);
		free (*lastbuffer);
		*lastbuffer = tmp;
		return (line);
	}
	line = ft_substr(*lastbuffer, 0, ft_strlen(*lastbuffer));
	free (*lastbuffer);
	*lastbuffer = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*lastbuffer;
	char		*buffer;
	char		*line;
	char		*newline_pos;
	ssize_t		bytes_read;

	if (!(ft_check(fd, &lastbuffer, &buffer, &bytes_read)))
		return (NULL);
	while (!(ft_strchr(lastbuffer, '\n')) && lastbuffer != NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		lastbuffer = ft_cat_n_check(lastbuffer, buffer);
		if (!lastbuffer)
			return (ft_handle_error(&buffer, &lastbuffer));
	}
	newline_pos = ft_strchr(lastbuffer, '\n');
	free(buffer);
	if (!lastbuffer || !*lastbuffer)
		return (ft_handle_error(NULL, &lastbuffer));
	line = ft_return_next_line(newline_pos, &lastbuffer);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("get_next_line.h", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}*/
