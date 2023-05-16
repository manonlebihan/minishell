/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:23:12 by mle-biha          #+#    #+#             */
/*   Updated: 2022/08/19 15:15:06 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(size_t nb, char *base)
{
	int	i;

	i = 0;
	if (nb < 16)
		i += ft_putchar(base[nb]);
	else if (nb >= 16)
	{
		i += ft_puthexa(nb / 16, base);
		i += ft_puthexa(nb % 16, base);
	}
	return (i);
}
