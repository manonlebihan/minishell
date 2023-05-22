/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:35:56 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 19:41:53 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env_var(t_env *e, char **env)
{
	char	*s;

	while (*env)
	{
		s = ft_strchr(*env, '=');
		s[0] = 0;
		s++;
		if (add_env_value(e, *env, s) == 1)
			return (1);
		env++;
	}
	return (0);
}

t_shell	*init_shell_var(void)
{
	t_shell	*s;

	s = malloc(sizeof(t_shell)); // check malloc
	//check_malloc_exit(s);
	if (s == NULL)
		exit(EXIT_FAILURE);
	s->exit = 0;
	s->last_cmd_status = 0;
	return (s);
}

int	main(int argc, char **argv, char **env)
{
	int		status;
	t_env	*e;
	t_shell	*s;

	(void)argc;
	(void)argv;
	status = 0;
	s = init_shell_var();
	/* if (s)
	{ */
		e = init_env();
		check_malloc_exit(e, s); // => OK
		if (init_env_var(e, env) == 1)
		{
			free(s);
			free(e);
			exit(EXIT_FAILURE);
		}
		minishell(s, e);
		status = s->last_cmd_status;
		free_shell(s);
		free_env(e);
	//}
	exit (status);
}
