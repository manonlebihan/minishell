/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:48:17 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/17 11:53:49 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(t_token *token)
{
	return (token && (token->type == TOKEN_TYPE_PIPE
			|| token->type == TOKEN_TYPE_REDIRECT));
}

t_node	*tree_simple_cmd(t_token **tokens, int *i, t_env *env)
{
	t_token	**t;
	t_data	*data;
	int		argc;
	int		idx;

	argc = 0;
	idx = *i;
	t = tokens;
	while (t[idx] && !is_separator(t[idx]))
	{
		argc++;
		idx++;
	}
	data = ft_calloc(1, sizeof(t_data)); // check malloc
	data->parameters = ft_calloc(1, sizeof(t_parameters)); // check malloc
	data->parameters->env = env;
	data->parameters->argc = argc;
	data->parameters->argv = ft_calloc(argc + 1, sizeof(char *)); // check malloc
	idx = 0;
	while (idx < argc)
	{
		data->parameters->argv[idx++] = ft_strdup(tokens[*i]->str); // check malloc
		(*i)++;
	}
	data->parameters->argv[idx] = NULL;
	return (get_new_node(NODE_TYPE_SIMPLE_CMD, NODE_SUBTYPE_NONE, data));
}

t_node	*tree_cmd(t_token **tokens, int *i, t_env *env)
{
	t_node	*node;
	t_node	*new;

	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_REDIRECT)
	{
		(*i)++;
		node = tree_redirects(tokens, i, env, tokens[(*i) - 1]->subtype);
	}
	else
	{
		node = tree_simple_cmd(tokens, i, env);
		while (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_REDIRECT)
		{
			(*i)++;
			new = tree_redirects(tokens, i, env, tokens[(*i) - 1]->subtype);
			new->left = node;
			node = new;
		}
	}
	return (node);
}

t_node	*tree_minishell_cmd(t_token **tokens, int *i, t_env *env)
{
	t_node	*node;
	t_node	*new;

	node = tree_cmd(tokens, i, env);
	if (tokens[*i] && tokens[*i]->type == TOKEN_TYPE_PIPE)
	{
		(*i)++;
		new = get_new_node(NODE_TYPE_PIPE, NODE_SUBTYPE_NONE, NULL);
		new->left = node;
		new->right = tree_minishell_cmd(tokens, i, env);
		node = new;
	}
	return (node);
}
