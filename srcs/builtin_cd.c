/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:14 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:55:35 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_paths_return(int rc, t_parameters *p, char *newpwd, char *oldpwd)
{
	if (newpwd != p->argv[1])
	{
		free(newpwd);
	}
	free(oldpwd);
	return (rc);
}

int	builtin_cd(t_shell *shell, t_parameters *p)
{
	char	*newpwd;
	char	*oldpwd;

	if (p->argc > 2)
	{
		print_msg_err(p->argv[0], NULL, "too many arguments");
		shell->last_cmd_status = EXIT_STATUS_BUILTIN_ERROR;
		return (1);
	}
	oldpwd = ft_strdup(get_env_value(p->env, "PWD")); // check malloc
	if (p->argc == 1)
		newpwd = ft_strdup(get_env_value(p->env, "HOME")); // check malloc
	else
		if (!ft_strcmp(p->argv[1], "-"))
			newpwd = ft_strdup(get_env_value(p->env, "OLDPWD")); // check malloc
		else
			newpwd = p->argv[1];
	if (newpwd == NULL || chdir(newpwd))
	{
		print_msg_err(p->argv[0], newpwd, "no such file or directory");
		shell->last_cmd_status = EXIT_STATUS_BUILTIN_ERROR;
		return (free_paths_return(1, p, newpwd, oldpwd));
	}
	if (p->argv[1] && !ft_strcmp(p->argv[1], "-"))
		printf("%s\n", newpwd);
	add_env_value(p->env, "OLDPWD", oldpwd);
	add_env_value(p->env, "PWD", newpwd);
	shell->last_cmd_status = EXIT_STATUS_NO_ERROR;
	return (free_paths_return(0, p, newpwd, oldpwd));
}
