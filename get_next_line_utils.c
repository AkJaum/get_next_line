#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
	char	*sdest;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (str[size] != '\0')
		size++;
	sdest = malloc(size + 1);
	if (!sdest)
		return (NULL);
	while (i < size)
	{
		sdest[i] = str[i];
		i++;
	}
	sdest[i] = '\0';
	return (sdest);
}

char	*ft_strchr(const char *str, int search_str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)search_str)
			return ((char *)str + i);
		i++;
	}
	if ((char)search_str == '\0')
		return ((char *) str + i);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	ii;
	size_t	lentotal;

	i = 0;
	ii = 0;
	while (dest[i] != '\0')
		i++;
	while (src[ii] != '\0')
		ii++;
	lentotal = ii + i;
	ii = 0;
	while (src[ii] != '\0')
	{
		dest[i] = src[ii];
		i++;
		ii++;
	}
	dest[i] = '\0';
	i++;
	return (lentotal);
}

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}