/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:13:29 by mle-biha          #+#    #+#             */
/*   Updated: 2023/01/24 16:35:32 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 42

char	*free_return(char *to_return, char *str1, char *str2);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_malloc_bzero(size_t len);
size_t	ft_strlen(const char *str);

#endif
