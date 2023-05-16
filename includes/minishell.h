/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:36:05 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 15:06:39 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/** SYSTEM INCLUDES **/
# include <stdlib.h>
# include <unistd.h>
# include "readline/readline.h"
# include <readline/history.h> // might be needed

/** LIBFT **/
# include "libft.h"

/** DEFINES **/
# define ENV_INIT "_ENV_HEADER_"

/** STRUCTS **/
typedef struct env_s
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	env_t;

typedef struct shell_s
{
	int	exit;
	int	last_cmd_status;
}	shell_t;

/** MAIN FUNC **/

#endif