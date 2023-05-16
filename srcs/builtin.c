/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:22:30 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:23:00 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

builtin_command_t	get_builtin_command(char *command)
{
	static char					*commands[] = {"cd", "pwd", "echo", "env", "exit", NULL};
	static builtin_command_t	builtin_commands[] = {&builtin_cd, &builtin_pwd, &builtin_echo, &builtin_env, &builtin_exit};
	int 						i;

	i = 0;
	while (commands[i])
	{
		if (!ft_strcmp(commands[i], command))
			return (builtin_commands[i]);
		i++;
	}
	return (NULL);
}