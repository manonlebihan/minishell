/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:40:03 by mle-biha          #+#    #+#             */
/*   Updated: 2022/08/30 14:09:14 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(va_list arg)
{
	int				i;
	unsigned long	p;

	i = 0;
	p = va_arg(arg, unsigned long);
	if ((void *) p == NULL)
		i += ft_putstr("(nil)");
	else
	{
		i += ft_putstr("0x");
		i += ft_puthexa(p, "0123456789abcdef");
	}
	return (i);
}
