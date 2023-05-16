/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:19:19 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 19:19:20 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_shell *shell, t_parameters *p)
{
	shell->last_cmd_status = EXIT_STATUS_NO_ERROR;
	if (p->argc > 1)
	{
		if (!ft_isnumeric(p->argv[1]))
		{
			shell->last_cmd_status = EXIT_STATUS_BUILTIN_ERROR;
			print_msg_err(p->argv[0], p->argv[1], "numeric argument required");
		}
		else
			shell->last_cmd_status = ft_atoi(p->argv[1]);
	}
	shell->exit = 1;
	return (shell->last_cmd_status);
}
