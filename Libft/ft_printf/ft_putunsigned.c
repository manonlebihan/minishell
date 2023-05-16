/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:39:44 by mle-biha          #+#    #+#             */
/*   Updated: 2022/08/19 14:52:26 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int n)
{
	int	i;

	i = 0;
	if (n < 10)
		i += ft_putchar('0' + n);
	else
	{
		i += ft_putunsigned(n / 10);
		i += ft_putunsigned(n % 10);
	}
	return (i);
}
