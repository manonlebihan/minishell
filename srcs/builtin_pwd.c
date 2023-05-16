/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:38 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:51:27 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(shell_t *shell, parameters_t *p)
{
	char	buf[MAX_PATH_SIZE];

	shell->last_cmd_status = EXIT_STATUS_GENERAL_ERROR;
	if (getcwd(buf, MAX_PATH_SIZE))
	{
		shell->last_cmd_status = EXIT_STATUS_NO_ERROR;
		print_std(buf);
	}
	return (shell->last_cmd_status);
}
