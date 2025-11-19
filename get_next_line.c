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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	if (start >= i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	subs = malloc(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

void    *ft_handle_error(char **buffer, char **lastbuffer)
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

char    *ft_cat_n_check(char *lastbuffer, char *buffer)
{
//Concatena lastbuffer e buffer em uma nova string e retorna
    char *temp;
    if (!lastbuffer)
        return ft_strdup(buffer);
    temp = malloc(ft_strlen(lastbuffer) + ft_strlen(buffer) + 1);
    if (!temp)
        return (NULL);
    ft_strcpy(temp, lastbuffer);
    ft_strcat(temp, buffer);
    free(lastbuffer);
    return (temp);
}

void *ft_check_is_valid(int fd, char **lastbuffer, char **buffer, ssize_t *bytes_read)
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
        {
            free(*buffer);
            return (NULL);
        }
        (*buffer)[*bytes_read] = '\0';
        *lastbuffer = ft_strdup(*buffer);
        if (!*lastbuffer)
        {
            free(*buffer);
            return (NULL);
        }
    }
    return (lastbuffer);
}

char	*get_next_line(int fd)
{
    static char *lastbuffer;
    char    *buffer;
    char    *line;
    char    *newline_pos;
    ssize_t bytes_read;

    if (!(ft_check_is_valid(fd, &lastbuffer, &buffer, &bytes_read)))
        return (NULL);
    //Procura por uma nova linha na leitura acumulada
    while (!(newline_pos = ft_strchr(lastbuffer, '\n')) && lastbuffer != NULL)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buffer[bytes_read] = '\0';
        lastbuffer = ft_cat_n_check(lastbuffer, buffer);
        if (!lastbuffer)
            return (ft_handle_error(&buffer, &lastbuffer));
    }
    free(buffer);
    //Verifica se há algo válido a retornar em lastbuffer
    if (!lastbuffer || !*lastbuffer)
        return (ft_handle_error(NULL, &lastbuffer));
    //Caso encontre uma nova linha, extrai todo o conteudo até '\n'
    if (newline_pos)
    {
        size_t line_length = newline_pos - lastbuffer + 1;
        line = ft_substr(lastbuffer, 0, line_length);
        if (!line)
            return ft_handle_error(NULL, &lastbuffer);
        char *new_lastbuffer = ft_substr(lastbuffer, line_length, ft_strlen(lastbuffer) - line_length);
        free(lastbuffer);
        lastbuffer = new_lastbuffer;
        return line;
    }
    //Se não houver nova linha, retorna todo o conteudo restante
    line = ft_strdup(lastbuffer);
    free(lastbuffer);
    lastbuffer = NULL;
    return (line);
}
        
    /*if (ft_strchr(lastbuffer, '\n'))
    {
        // Extrai a linha até o próximo '\n' ou o fim da string
        line = malloc(BUFFER_SIZE + 1);
        if!line)
            return (NULL);
        while (lastbuffer[i] != '\0' && lastbuffer[i] != '\n')
        {
            line[i] = lastbuffer[i];
            i++;
        }
        if (lastbuffer[i] == '\0')
            return (line);
        else if (lastbuffer[i] == '\n')
            line[i] = '\n';
        return (line);
    }*/
    
    /*    if (newline_pos)
    {
        size_t line_length;
        line_length = newline_pos - lastbuffer + 1;
        line = malloc(line_length + 1);
        if (!line)
            return (NULL);
        i = 0;
        while (i < line_length)
        {
            line[i] = lastbuffer[i];
            i++;
        }
        line[line_length] = '\0';
    // Atualiza lastbuffer para remover a linha retornada para não duplicar na proxima chamada
        char *new_lastbuffer;
        new_lastbuffer = ft_strdup(lastbuffer + line_length);
        free(lastbuffer);
        lastbuffer = new_lastbuffer;
        return (line);
        line = ft_substr(lastbuffer, line_length, ft_strlen(lastbuffer) - line_length);
    }*/