/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:14:13 by mle-biha          #+#    #+#             */
/*   Updated: 2022/10/15 17:14:45 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_return(char *str1, char *str2, char *to_return)
{
	if (str1 != NULL)
		free(str1);
	if (str2 != NULL)
		free(str2);
	return (to_return);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_malloc_bzero(size_t len)
{
	char		*line;
	size_t		i;

	line = (char *)malloc(sizeof(char) * len);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = '\0';
		i++;
	}
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	if (c > 256)
		c %= 256;
	while (*s != c)
	{
		s++;
		if (*s == '\0')
			return (NULL);
	}
	return ((char *)s);
}
