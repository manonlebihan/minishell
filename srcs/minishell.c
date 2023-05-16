/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:13:10 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:20:46 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_tree(shell_t *shell, t_node *node)
{
	builtin_command_t	builtin_command;

	if (node->type == NODE_TYPE_SIMPLE_CMD)
	{
		builtin_command = get_builtin_command(node->data->parameters->argv[0]);
		if (builtin_command != NULL)
			builtin_command(shell, node->data->parameters);
		else
			extern_command(shell, node->data->parameters);
	}
	else if (node->type == NODE_TYPE_REDIRECT)
	{
		printf(" ==========================> TODO: manage redirect to file %s\n", node->data->file);
		// dup2/open/close
		execute_tree(shell, node->left);
	}
	else if (node->type == NODE_TYPE_PIPE)
	{
		printf(" ==========================> TODO: manage pipe\n");
		// pipe
		execute_tree(shell, node->left);
		execute_tree(shell, node->right);
	}
}

int	minishell(shell_t *shell, env_t *env)
{
	char	*line;
	t_node	*root;
	t_token	**tokens;

	while (!shell->exit)
	{
		line = readline("> ");
		tokens = tokenize(line);
		if (tokens)
		{
			// debug_tokens(tokens);
			if (!parse(tokens))
				print_err("syntax error\n");
			else
			{
				root = NULL;
				root = build_tree(tokens, env);
				//debug_tree(root, 0);
				execute_tree(shell, root);
				free_tree(root);
			}
			free_tokens(tokens);
		}
		free(line);
	}
}