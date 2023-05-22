/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:33 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 14:54:38 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	if (string[*string_index] == '|')
	{
		tokens[(*tokens_index)++] = get_new_token(TOKEN_TYPE_PIPE,
				TOKEN_SUBTYPE_NONE, NULL);
		string[*string_index] = '\0';
		*prev_was_sep = 1;
		return (1);
	}
	return (0);
}

int	check_redirect_in(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	if (string[*string_index] == '>')
	{
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_REDIRECT,
				TOKEN_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE, NULL);
		if (string[*string_index + 1] == '>')
		{
			tokens[*tokens_index]->subtype = TOKEN_SUBTYPE_TYPE_REDIRECT_IN_APPEND_FILE;
			(*string_index)++;
		}
		(*tokens_index)++;
		string[*string_index] = '\0';
		*prev_was_sep = 1;
		return (1);
	}
	return (0);
}

int	check_redirect_out(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	if (string[*string_index] == '<')
	{
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_REDIRECT,
				TOKEN_SUBTYPE_TYPE_REDIRECT_OUT, NULL);
		if (string[*string_index + 1] == '<')
		{
			tokens[*tokens_index]->subtype = TOKEN_SUBTYPE_TYPE_REDIRECT_HEREDOC;
			(*string_index)++;
		}
		string[*string_index] = '\0';
		(*tokens_index)++;
		*prev_was_sep = 1;
		return (1);
	}
	return (0);
}
