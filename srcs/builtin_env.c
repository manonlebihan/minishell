/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:37:08 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:55:35 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell, t_parameters *p)
{
	if (p->argc == 1)
	{
		shell->last_cmd_status = EXIT_STATUS_NO_ERROR;
		list_env_value(p->env);
	}
	else
	{
		shell->last_cmd_status = EXIT_STATUS_BUILTIN_ERROR;
		print_msg_err(p->argv[0], NULL, "too many arguments");
	}
	return (shell->last_cmd_status);
}
