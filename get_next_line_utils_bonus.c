/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jneris-d <tbpjaum@outlook.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by jneris-d          #+#    #+#             */
/*   Updated: 2025/11/24 12:50:55 by jneris-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	if (start >= i)
	{
		subs = malloc(1);
		ft_strcpy(subs, "");
		return (subs);
	}
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
