/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:59:25 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/17 11:55:57 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_io_redirect(t_token **tokens, int *i, int *rc)
{
	if (!*rc)
		return ;
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_WORD)
		(*i)++;
	else // syntax error
		*rc = 0;
}

void	syntax_redirects(t_token **tokens, int *i, int *rc)
{
	if (!*rc)
		return ;
	syntax_io_redirect(tokens, i, rc);
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_REDIRECT)
	{
		(*i)++;
		syntax_redirects(tokens, i, rc);
	}
}

void	syntax_simple_cmd(t_token **tokens, int *i, int *rc)
{
	if (!*rc)
		return ;
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_WORD)
	{
		(*i)++;
		while (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_WORD)
			(*i)++;
	}
	else // syntax error
		*rc = 0;
}

void	syntax_cmd(t_token **tokens, int *i, int *rc)
{
	if (!*rc)
		return ;
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_REDIRECT)
	{
		(*i)++;
		syntax_redirects(tokens, i, rc);
	}
	else
		syntax_simple_cmd(tokens, i, rc);
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_REDIRECT)
	{
		(*i)++;
		syntax_redirects(tokens, i, rc);
	}
}

void	syntax_minishell_cmd(t_token **tokens, int *i, int *rc)
{
	if (!*rc)
		return ;
	syntax_cmd(tokens, i, rc);
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_PIPE)
	{
		(*i)++;
		syntax_minishell_cmd(tokens, i, rc);
	}
}
