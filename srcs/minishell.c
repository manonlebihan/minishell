/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:13:10 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 15:58:48 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(shell_t *shell, env_t *env)
{
	char	*line;
	t_node	*root;
	t_token	**tokens;

	while (!shell->exit)
	{
		line = readline(">g ");
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
				debug_tree(root, 0);
				execute_tree(shell, root);
				free_tree(root);
			}
			free_tokens(tokens);
		}
		free(line);
	}
}