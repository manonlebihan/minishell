/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:24:09 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:30:59 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute(char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

void	execute_command(shell_t *s, parameters_t *p)
{
	pid_t	pid = 0;
	int	status = 0;

	pid = fork();
	if (pid == -1)
		print_msg_err(p->argv[0], NULL, "cannot fork");
	else if (pid > 0) 
	{
		// father
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else 
	{
		// son
		if (execve(p->argv[0], p->argv, get_env_array(p->env)) == -1)
			print_msg_err(p->argv[0], NULL, "cannot exex");
		exit(EXIT_FAILURE);
	}
}

char	*get_path(parameters_t *p)
{
	char	**paths;
	char	*env_path;
	char	*path;

	env_path = get_env_value(p->env, "PATH");
	path = NULL;
	if (env_path)
	{
		paths = ft_split(ft_strdup(env_path), ':'); // check malloc
		if (paths)
		{
			while (*paths)
			{
				path = ft_strjoin(ft_strjoin(*paths, "/"), p->argv[0]); // check malloc
				if (access(path, X_OK) == 0)
				{
					break;
				}
				*paths++;
				free(path);
				path = NULL;
			}
		}
	}
	return (path);
}

int	extern_command(shell_t *s, parameters_t *p)
{
	char	*path;

	if (is_absolute(p->argv[0]))
		execute_command(s, p);
	else
	{
		path = get_path(p);
		if (path)
		{
			p->argv[0] = ft_strdup(path); // check malloc
			execute_command(s, p);
		}
		else
			print_msg_err(p->argv[0], NULL, "command not found");
	}
	return (s->last_cmd_status);
}