/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:44:17 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 18:01:54 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
int	ft_isnumeric(char *str)
{
	if (!*str || (!ft_issign(*str) && !ft_isdigit(*str)))
		return 0;
	*str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return 0;
	return 1;
}