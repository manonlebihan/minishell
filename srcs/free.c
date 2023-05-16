/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:26:49 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 19:15:20 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_node *node)
{
	if (node)
	{
		free_tree(node->left);
		free_tree(node->right);
		// TODO: be sure to free all allocated memory (especially data)
		free(node);
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	**t;

	t = tokens;
	while (*t)
		free(*t++);
	free(tokens);
}

void	free_env(t_env *env)
{
	t_env	*an_env;

	while (env)
	{
		free(env->key);
		free(env->value);
		an_env = env->next;
		free(env);
		env = an_env;
	}
}

void	free_shell(t_shell *shell)
{
	free(shell);
}
