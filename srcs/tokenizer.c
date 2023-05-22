/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:59:34 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 15:10:32 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type_label(t_token *token)
{
	if (token->type == TOKEN_TYPE_NONE)
		return ("NONE");
	if (token->type == TOKEN_TYPE_WORD)
		return ("WORD");
	if (token->type == TOKEN_TYPE_PIPE)
		return ("PIPE");
	if (token->type == TOKEN_TYPE_REDIRECT)
		return ("REDIRECT");
	if (token->type == TOKEN_TYPE_DOUBLE_QUOTES)
		return ("DOUBLE QUOTES");
	if (token->type == TOKEN_TYPE_SINGLE_QUOTES)
		return ("SIMPLE QUOTES");
	return ("UNKNOWN!");
}

char	*get_subtype_label(t_token *token)
{
	if (token->subtype == TOKEN_SUBTYPE_NONE)
		return ("NONE");
	if (token->subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE)
		return ("TRUNC FILE");
	if (token->subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_IN_APPEND_FILE)
		return ("APPEND FILE");
	if (token->subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_OUT)
		return ("OUT");
	if (token->subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN!");
}

t_token	*get_new_token(int type, int subtype, char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token)); // check malloc
	if (token)
	{
		token->type = type;
		token->subtype = subtype;
		token->str = str;
	}
	return (token);
}

t_token	**init_tokens(char *string)
{
	int	nb_words;

	if (!string[0])
		return (NULL);
	nb_words = count_words(string);
	if (!nb_words)
		return (NULL);
	return (ft_calloc(nb_words + 1, sizeof(t_token)));
}

t_token	**tokenize(char *string)
{
	t_token	**tokens;
	int		prev_was_sep;
	int		tokens_index;
	int		string_index;

	tokens = init_tokens(string);
	if (tokens == NULL)
		return (NULL);
	tokens_index = 0;
	string_index = 0;
	prev_was_sep = 1;
	while (string[string_index])
		check_all(string, tokens, &string_index, &tokens_index, &prev_was_sep);
	return (tokens);
}
