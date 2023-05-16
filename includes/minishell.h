/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:36:05 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:09:45 by mle-biha         ###   ########.fr       */
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

# define TOKEN_TYPE_NONE			0
# define TOKEN_TYPE_WORD			1
# define TOKEN_TYPE_PIPE			2
# define TOKEN_TYPE_REDIRECT		3
# define TOKEN_TYPE_DOUBLE_QUOTES	4
# define TOKEN_TYPE_SINGLE_QUOTES	5

# define TOKEN_SUBTYPE_NONE							0
# define TOKEN_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE	1
# define TOKEN_SUBTYPE_TYPE_REDIRECT_IN_APPEND_FILE	2
# define TOKEN_SUBTYPE_TYPE_REDIRECT_OUT			3
# define TOKEN_SUBTYPE_TYPE_REDIRECT_HEREDOC		4

# define NODE_TYPE_NONE			0
# define NODE_TYPE_PIPE			1
# define NODE_TYPE_SIMPLE_CMD	2
# define NODE_TYPE_REDIRECT		3

# define NODE_SUBTYPE_NONE							0
# define NODE_SUBTYPE_TYPE_REDIRECT_IN_TRUNC_FILE	1
# define NODE_SUBTYPE_TYPE_REDIRECT_IN_APPEND_FILE	2
# define NODE_SUBTYPE_TYPE_REDIRECT_OUT				3
# define NODE_SUBTYPE_TYPE_REDIRECT_HEREDOC			4

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

typedef struct parameters_s
{
	int		argc;
	char	**argv;
	env_t	*env;
}	parameters_t;

typedef union u_data
{
	parameters_t	*parameters;
	char			*file;
	char			*heredoc;
}	t_data;

typedef struct s_node
{
	int				type;
	int				subtype;
	t_data			*data;
	int				stdin;
	int				stdout;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_token
{
	int		type;
	int		subtype;
	char	*str;
}	t_token;

/** MAIN FUNC **/

#endif