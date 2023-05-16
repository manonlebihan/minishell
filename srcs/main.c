/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:35:56 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 15:11:41 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_var(env_t *e, char **env)
{
	char	*s;

	while (*env)
	{
		s = ft_strchr(*env, '=');
		s[0] = 0;
		s++;
		add_env_value(e, *env, s);
		*env++;
	}
}

shell_t	*init_shell_var(void)
{
	shell_t	*s;

	s = malloc(sizeof(shell_t)); // check malloc
	if (s)
	{
		s->exit = 0;
		s->last_cmd_status = 0;
	}
	return (s);
}

int	main(int argc, char **argv, char **env)
{
	int		status;
	env_t	*e;
	shell_t	*s;

	(void)argc;
	(void)argv;
	status = 0;
	s = init_shell_var();
	if (s)
	{
		e = init_env();
		init_env_var(e, env);
		minishell(s, e);
		status = s->last_cmd_status;
		free_shell(s);
		free_env(e);
	}
	exit (status);
}
