/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:07:09 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/17 11:53:55 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_node	*tree_redirects(t_token **tokens, int *i, t_env *env, int subtype)
{
	t_data	*data;

	(void) env;
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

t_node	*build_tree(t_token **tokens, t_env *env)
{
	int	i;

	i = 0;
	return (tree_minishell_cmd(tokens, &i, env));
}
