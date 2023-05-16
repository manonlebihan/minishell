/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:12:54 by mle-biha          #+#    #+#             */
/*   Updated: 2022/10/15 17:34:41 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (s1 == NULL)
	{
		s1 = ft_malloc_bzero(1);
		if (s1 == NULL)
			return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = ft_malloc_bzero(len1 + len2 + 1);
	if (s3 == NULL)
		return (free_return(s1, NULL, NULL));
	i = -1;
	while (s1[++i] != '\0')
		s3[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		s3[len1 + i] = s2[i];
	return (free_return(s1, NULL, s3));
}

char	*ft_read_file(int fd, char *stash)
{
	int			chars_read;
	char		*buf;

	buf = ft_malloc_bzero(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, buf, BUFFER_SIZE);
		if (chars_read == -1)
			return (free_return(buf, NULL, NULL));
		buf[chars_read] = '\0';
		if (chars_read > 0)
			stash = ft_strjoin_free(stash, buf);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	return (free_return(buf, NULL, stash));
}

char	*ft_get_line_before_eos(char *str)
{
	char		*line;
	int			i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_malloc_bzero(i + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	return (line);
}

char	*ft_get_line_after_eos(char *str)
{
	char		*line;
	int			i;
	int			j;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i + j] != '\0')
		j++;
	line = ft_malloc_bzero(j + 1);
	j = 0;
	if (line != NULL)
	{
		while (str[i + j] != '\0')
		{
			line[j] = str[i + j];
			j++;
		}
	}
	return (free_return(str, NULL, line));
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stash = ft_read_file(fd, stash);
	if (stash == NULL || stash[0] == '\0')
		return (free_return(stash, NULL, NULL));
	line = ft_get_line_before_eos(stash);
	if (line == NULL)
		return (free_return(stash, NULL, NULL));
	stash = ft_get_line_after_eos(stash);
	if (stash == NULL)
		return (free_return(stash, line, NULL));
	return (line);
}
