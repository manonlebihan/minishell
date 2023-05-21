/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:59:34 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/21 23:04:31 by mle-biha         ###   ########.fr       */
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

	token = malloc(sizeof(t_token));
	if (token)
	{
		token->type = type;
		token->subtype = subtype;
		token->str = str;
	}
	return (token);
}

int	check_pipe(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	if (string[*string_index] == '|') 
	{
		tokens[(*tokens_index)++] = get_new_token(TOKEN_TYPE_PIPE, TOKEN_SUBTYPE_NONE, NULL);
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
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_REDIRECT, TOKEN_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE, NULL);
		if (string[*string_index + 1] == '>') {
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
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_REDIRECT, TOKEN_SUBTYPE_TYPE_REDIRECT_OUT, NULL);
		if (string[*string_index + 1] == '<') {
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

int	check_double_quote(char *string, t_token **tokens, int *string_index,
	int *tokens_index)
{
	if (string[*string_index] == '"')
	{
		tokens[*tokens_index] = get_new_token(TOKEN_TYPE_DOUBLE_QUOTES,
			TOKEN_SUBTYPE_NONE, &(string[*string_index]));
		(*string_index)++;
		while (*string && string[(*string_index)++] != '"');
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
		while (*string && string[(*string_index)++] != '\'');
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

void	check_all(char *string, t_token **tokens, int *string_index,
	int *tokens_index, int *prev_was_sep)
{
	if (check_pipe(string, tokens, string_index, tokens_index, prev_was_sep)
		|| check_redirect_in(string, tokens, string_index, tokens_index, prev_was_sep)
		|| check_redirect_out(string, tokens, string_index, tokens_index, prev_was_sep)
		|| check_double_quote(string, tokens, string_index, tokens_index)
		|| check_single_quote(string, tokens, string_index, tokens_index)
		|| check_space(string, string_index, prev_was_sep)
		|| check_no_space(string, tokens, string_index, tokens_index, prev_was_sep))
	{
		;
	}
	(*string_index)++;
}

t_token	**init_tokens(char *string)
{
	int	nb_words;

	if (!string[0])
		return (NULL);
	nb_words = count_words(string);
	if (!nb_words)
		return (NULL);
	return (calloc(nb_words + 1, sizeof(t_token)));
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
