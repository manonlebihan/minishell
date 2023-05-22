/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:03:44 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 15:04:00 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (*string == '"')
		{
			string++;
			while (*string && *string++ != '"')
				;
			nb++;
		}
		else if (*string == '\'')
		{
			string++;
			while (*string && *string++ != '\'')
				;
			nb++;
		}
		else if (*string == ' ')
			prev_was_sep = 1;
		else if (*string != ' ' && prev_was_sep)
		{
			nb++;
			prev_was_sep = 0;
		}
		string++;
	}
	return (nb);
}
