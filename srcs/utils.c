/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:03:44 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 15:42:03 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	divide_count_words(char *string, int *nb, int *prev_was_sep)
{
	if (*string == '"')
	{
		*string += 1;
		while (*string && *string++ != '"')
			;
		*nb += 1;
	}
	else if (*string == '\'')
	{
		*string += 1;
		while (*string && *string++ != '\'')
			;
		*nb += 1;
	}
	else if (*string == ' ')
		*prev_was_sep = 1;
	else if (*string != ' ' && *prev_was_sep)
	{
		*nb += 1;
		*prev_was_sep = 0;
	}
}

int	count_words(char *string)
{
	int	prev_was_sep;
	int	nb;

	nb = 0;
	prev_was_sep = 1;
	while (*string)
	{
		if (*string == '|' || *string == '<' || *string == '>')
			nb++;
		divide_count_words(string, &nb, &prev_was_sep);
		string++;
	}
	return (nb);
}
