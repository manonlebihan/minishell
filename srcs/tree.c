/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:07:09 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:18:09 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(t_token *token)
{
	return (token && (token->type == TOKEN_TYPE_PIPE || token->type == TOKEN_TYPE_REDIRECT));
}

t_node	*get_new_node(int type, int subtype, t_data *data)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node)); // check malloc
	if (node)
	{
		node->type = type;
		node->subtype = subtype;
		node->data = data;
		node->stdin = STDIN_FILENO;
		node->stdout = STDOUT_FILENO;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

t_node	*tree_redirects(t_token **tokens, int *i, env_t *env, int subtype)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data)); // check malloc
	if (subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE
		|| subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_IN_APPEND_FILE
		|| subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_OUT)
		data->file = ft_strdup(tokens[*i]->str); // check malloc
	else if (subtype == TOKEN_SUBTYPE_TYPE_REDIRECT_HEREDOC)
		data->heredoc = ft_strdup(tokens[*i]->str); // check malloc
	(*i)++;
	return (get_new_node(NODE_TYPE_REDIRECT, subtype, data));
}

t_node	*tree_simple_cmd(t_token **tokens, int *i, env_t *env)
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
	data->parameters = ft_calloc(1, sizeof(parameters_t)); // check malloc
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

t_node	*tree_cmd(t_token **tokens, int *i, env_t *env)
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

t_node	*tree_minishell_cmd(t_token **tokens, int *i, env_t *env)
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

t_node	*build_tree(t_token **tokens, env_t *env)
{
	int	i;

	i = 0;
	return (tree_minishell_cmd(tokens, &i, env));
}