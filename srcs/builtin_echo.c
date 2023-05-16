/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:56 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 18:38:11 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_simple_quotes(char *str)
{
	return (str && str[0] && str[0] == '\'' && str[ft_strlen(str) - 1] == '\'');
}

int	is_double_quotes(char *str)
{
	return (str && str[0] && str[0] == '"' && str[ft_strlen(str) - 1] == '"');
}

int	has_dollar(char *str)
{
	int	rc;

	rc = (ft_strchr(str, '$') != NULL);
	return (rc);
}

char	*clean_string(char *str)
{
	char	*tmp;

	if (is_simple_quotes(str))
		return (ft_substr(str, 1, ft_strlen(str) - 2)); // check malloc
	else if (is_double_quotes(str))
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 2); // check malloc
		if (!has_dollar(tmp))
			return (tmp);
		else
			return ("manage dollar !!!");
	}
	else 
		return (str);
}

int	builtin_echo(t_shell *shell, t_parameters *p)
{
	int	print_new_line;
	int	i;

	print_new_line = 1;

	shell->last_cmd_status = EXIT_STATUS_NO_ERROR;
	if (p->argc > 1)
	{
		i = 1;
		if (ft_strcmp(p->argv[i], "-n") == 0)
		{
			i++;
			print_new_line = 0;
		}
		while (i < p->argc)
		{
			print_std_no_nl(ft_strjoin(clean_string(p->argv[i]), " ")); // check malloc
			i++;
		}
	}
	if (print_new_line == 1)
		print_std("");
	return (shell->last_cmd_status);
}
