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

char    *ft_cat_n_check(char *lastbuffer, char *buffer)
{
//Concatena lastbuffer e buffer em uma nova string e retorna
    char *temp;
    temp = malloc(ft_strlen(lastbuffer) + ft_strlen(buffer) + 1);
    if (!temp)
        return (NULL);
    ft_strcpy(temp, lastbuffer);
    ft_strcat(temp, buffer);
    free(lastbuffer);
    return (temp);
}

char	*get_next_line(int fd)
{
    static char *lastbuffer;
    char    buffer[BUFFER_SIZE + 1];
    char    *line;
    char    *newline_pos;
    ssize_t bytes_read;
    ssize_t i;
    
    //Verifica se o file descriptor é válido
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    // Lê do file descriptor para o buffer até encontrar um '\n'
    if (!lastbuffer)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            return (NULL);
        buffer[bytes_read] = '\0';
        lastbuffer = ft_strdup(buffer);
        if (!lastbuffer)
            return (NULL);
    }
    
    //Procura por uma nova linha na leitura acumulada
    while (!(newline_pos = ft_strchr(lastbuffer, '\n')) && lastbuffer != NULL)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            return (NULL);
        buffer[bytes_read] = '\0';
        lastbuffer = ft_cat_n_check(lastbuffer, buffer);
        if (!lastbuffer)
            return (NULL);
    }
    
    //Verifica se há algo válido a retornar em lastbuffer
    if (!lastbuffer || !*lastbuffer)
    {
        free(lastbuffer);
        lastbuffer = NULL;
        return NULL;
    }
    
    //Caso encontre uma nova linha, extrai todo o conteudo até '\n'
    if (newline_pos)
    {
        size_t line_length = newline_pos - lastbuffer + 1;
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
        char *new_lastbuffer = ft_strdup(lastbuffer + line_length);
        free(lastbuffer);
        lastbuffer = new_lastbuffer;
        return (line);
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
        if(!line)
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