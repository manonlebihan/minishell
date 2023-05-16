/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:55:23 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 18:02:16 by mle-biha         ###   ########.fr       */
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
			while (*string && *string++ != '"');
			nb++;
		}
		else if (*string == '\'')
		{
			string++;
			while (*string && *string++ != '\'');
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

t_token	**tokenize(char *string)
{
	t_token	**tokens;
	int		prev_was_sep;
	int		nb_words;
	int		i;

	if (!*string)
		return (NULL);
	nb_words = count_words(string);
	if (!nb_words)
		return (NULL);
	tokens = malloc((nb_words + 1) * sizeof(t_token)); // check malloc
	i = 0;
	prev_was_sep = 1;
	while (*string)
	{
		if (*string == '|') 
		{
			tokens[i++] = get_new_token(TOKEN_TYPE_PIPE, TOKEN_SUBTYPE_NONE, NULL);
			*string = 0;
			prev_was_sep = 1;
		}
		else if (*string == '>') 
		{
			tokens[i] = get_new_token(TOKEN_TYPE_REDIRECT, TOKEN_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE, NULL);
			if (*(string+1) == '>')
			{
				tokens[i]->subtype = TOKEN_SUBTYPE_TYPE_REDIRECT_IN_APPEND_FILE;
				*string++;
			}
			i++;
			*string = 0;
			prev_was_sep = 1;
		}
		else if (*string == '<')
		{
			tokens[i] = get_new_token(TOKEN_TYPE_REDIRECT, TOKEN_SUBTYPE_TYPE_REDIRECT_OUT, NULL);
			if (*(string+1) == '<')
			{
				tokens[i]->subtype = TOKEN_SUBTYPE_TYPE_REDIRECT_HEREDOC;
				*string++;
			}
			*string = 0;
			i++;
			prev_was_sep = 1;
		}
		else if (*string == '"')
		{
			tokens[i++] = get_new_token(TOKEN_TYPE_DOUBLE_QUOTES, TOKEN_SUBTYPE_NONE, string);
			*string++;
			while (*string && *string++ != '"');
			*string = '\0';			
		}
		else if (*string == '\'')
		{
			tokens[i++] = get_new_token(TOKEN_TYPE_SINGLE_QUOTES, TOKEN_SUBTYPE_NONE, string);
			*string++;
			while (*string && *string++ != '\'');
			*string = '\0';
		}
		else if (*string == ' ')
		{
			*string = '\0';
			prev_was_sep = 1;
		}
		else if (*string != ' ' && prev_was_sep)
		{
			tokens[i++] = get_new_token(TOKEN_TYPE_WORD, TOKEN_SUBTYPE_NONE, string);
			prev_was_sep = 0;
		}
		*string++;
	}
	tokens[i] = NULL;
	return (tokens);
}
