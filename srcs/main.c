/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:35:56 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 18:25:06 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_var(t_env *e, char **env)
{
	char	*s;

	while (*env)
	{
		s = ft_strchr(*env, '=');
		s[0] = 0;
		s++;
		add_env_value(e, *env, s);
		env++;
	}
}

t_shell	*init_shell_var(void)
{
	t_shell	*s;

	s = malloc(sizeof(t_shell)); // check malloc
	check_malloc_exit(s);
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
	if (s)
	{
		e = mainit_env();
		check_malloc_exit(e, s); // => OK
		init_env_var(e, env);
		minishell(s, e);
		status = s->last_cmd_status;
		free_shell(s);
		free_env(e);
	}
	exit (status);
}
