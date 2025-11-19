#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char *get_next_line(int fd);
char *ft_strdup(const char *s1);
char	*ft_strchr(const char *str, int search_str);
size_t ft_strlen(const char *s);
size_t	ft_strcpy(char *dest, const char *src);
size_t	ft_strcat(char *dest, const char *src);

#endif