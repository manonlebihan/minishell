/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:38:42 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/23 12:07:21 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_quote(char *string, t_token **tokens, int *string_index,
	int *tokens_index)
{
	if (string[*string_index] == '"')
	{
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_DOUBLE_QUOTES,
				TOKEN_SUBTYPE_NONE, &(string[*string_index]));
		(*string_index)++;
		while (*string && string[(*string_index)++] != '"')
			;
		string[*string_index] = '\0';
		(*tokens_index)++;
		return (1);
	}
	return (0);
}

int	check_single_quote(char *string, t_token **tokens, int *string_index,
	int *tokens_index)
{
	if (string[*string_index] == '\'')
	{
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_SINGLE_QUOTES,
				TOKEN_SUBTYPE_NONE, &(string[*string_index]));
		(*string_index)++;
		while (*string && string[(*string_index)++] != '\'')
			;
		string[*string_index] = '\0';
		(*tokens_index)++;
		return (1);
	}
	return (0);
}

int	check_space(char *string, int *string_index, int *prev_was_sep)
{
	if (string[*string_index] == ' ')
	{
		string[*string_index] = '\0';
		*prev_was_sep = 1;
		return (1);
	}
	return (0);
}

int	check_no_space(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	if (string[*string_index] != ' ' && *prev_was_sep)
	{
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_WORD,
				TOKEN_SUBTYPE_NONE, &(string[*string_index]));
		*prev_was_sep = 0;
		(*tokens_index)++;
		return (1);
	}
	return (0);
}

/* void	check_all(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	check_pipe(string, tokens, string_index, tokens_index, prev_was_sep)
	|| check_redirect_in(string, tokens, string_index, tokens_index, prev_was_sep)
	|| check_redirect_out(string, tokens, string_index, tokens_index, prev_was_sep)
	|| check_double_quote(string, tokens, string_index, tokens_index)
	|| check_single_quote(string, tokens, string_index, tokens_index)
	|| check_space(string, string_index, prev_was_sep)
	|| check_no_space(string, tokens, string_index, tokens_index, prev_was_sep);
	(*string_index)++;
} */

/* void	check_all(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	int	t;

	t = check_pipe(string, tokens, string_index, tokens_index, prev_was_sep)
			|| check_redirect_in(string, tokens, string_index, tokens_index, prev_was_sep);
	if (!t)
	{
		t = check_redirect_out(string, tokens, string_index, tokens_index, prev_was_sep)
			|| check_double_quote(string, tokens, string_index, tokens_index);
		if (!t)
		{
			t = check_single_quote(string, tokens, string_index, tokens_index)
				|| check_space(string, string_index, prev_was_sep);
			if (!t)
				check_no_space(string, tokens, string_index, tokens_index, prev_was_sep);
		}
	}
	(*string_index)++;
} */

void	check_all(char *string, t_token **tokens, int *j,
	int *i, int *prev_was_sep)
{
	if (!check_pipe(string, tokens, j, i, prev_was_sep))
	{
		if (!check_redirect_in(string, tokens, j, i, prev_was_sep))
			if (!check_redirect_out(string, tokens, j, i, prev_was_sep))
				if (!check_double_quote(string, tokens, j, i))
					if (!check_single_quote(string, tokens, j, i))
						if (!check_space(string, j, prev_was_sep))
							check_no_space(string, tokens, j, i, prev_was_sep);
	}
		(*j)++;
}
