/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:36:05 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 15:48:52 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/** SYSTEM INCLUDES **/
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "readline/readline.h"
# include <readline/history.h> // might be needed
# include <sys/types.h>
# include <sys/wait.h>

/** LIBFT **/
# include "libft.h"

/** DEFINES **/
# define ENV_INIT "_ENV_HEADER_"
# define MAX_PATH_SIZE 1024

# define TOKEN_TYPE_NONE			0
# define TOKEN_TYPE_WORD			1
# define TOKEN_TYPE_PIPE			2
# define TOKEN_TYPE_REDIRECT		3
# define TOKEN_TYPE_DOUBLE_QUOTES	4
# define TOKEN_TYPE_SINGLE_QUOTES	5

# define TOKEN_SUBTYPE_NONE						0
# define TOKEN_SUBTYPE_REDIRECT_IN_TRUNC_FILE	1
# define TOKEN_SUBTYPE_REDIRECT_IN_APPEND_FILE	2
# define TOKEN_SUBTYPE_REDIRECT_OUT				3
# define TOKEN_SUBTYPE_REDIRECT_HEREDOC			4

# define NODE_TYPE_NONE			0
# define NODE_TYPE_PIPE			1
# define NODE_TYPE_SIMPLE_CMD	2
# define NODE_TYPE_REDIRECT		3

# define NODE_SUBTYPE_NONE						0
# define NODE_SUBTYPE_REDIRECT_IN_TRUNC_FILE	1
# define NODE_SUBTYPE_REDIRECT_IN_APPEND_FILE	2
# define NODE_SUBTYPE_REDIRECT_OUT				3
# define NODE_SUBTYPE_REDIRECT_HEREDOC			4

# define EXIT_STATUS_NO_ERROR			0
# define EXIT_STATUS_GENERAL_ERROR		1
# define EXIT_STATUS_BUILTIN_ERROR		2
# define EXIT_STATUS_CANNOT_EXECUTE		126
# define EXIT_STATUS_COMMAND_NOT_FOUND	127
# define EXIT_STATUS_SIGNAL_ERROR_BASE	128
# define EXIT_STATUS_EXIT_CTRL_C		130

/** STRUCTS **/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int	exit;
	int	last_cmd_status;
}	t_shell;

typedef struct s_parameters
{
	int		argc;
	char	**argv;
	t_env	*env;
}	t_parameters;

typedef union u_data
{
	t_parameters	*parameters;
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

typedef int	(*t_builtin_command)(t_shell *, t_parameters *);

/** MAIN FUNC **/

/** BUILTIN FUNC **/
t_builtin_command	get_builtin_command(char *command);
int					builtin_cd(t_shell *shell, t_parameters *p);
int					builtin_echo(t_shell *shell, t_parameters *p);
int					builtin_env(t_shell *shell, t_parameters *p);
int					builtin_exit(t_shell *shell, t_parameters *p);
int					builtin_pwd(t_shell *shell, t_parameters *p);

/** CHECK ALL FUNC **/
void				check_all(char *string, t_token **tokens, int *string_index,
						int *tokens_index, int *prev_was_sep);

/** CHECK PIPES REDICRECTS FUNC **/
int					check_pipe(char *string, t_token **tokens,
						int *string_index, int *tokens_index,
						int *prev_was_sep);
int					check_redirect_in(char *string, t_token **tokens,
						int *string_index, int *tokens_index,
						int *prev_was_sep);
int					check_redirect_out(char *string, t_token **tokens,
						int *string_index, int *tokens_index,
						int *prev_was_sep);

/** ENV FUNC **/
t_env				*init_env(void);
t_env				*create_env(char *key, char *value);
char				*get_env_value(t_env *env, char *key);
void				add_env_value(t_env *env, char *key, char *value);
void				list_env_value(t_env *env);
char				**get_env_array(t_env *env);
t_env				*get_env(t_env *env, char *key);

/** EXTERN FUNC **/
int					extern_command(t_shell *s, t_parameters *p);

/** FREE FUNC **/
void				free_tree(t_node *node);
void				free_tokens(t_token **tokens);
void				free_env(t_env *env);
void				free_shell(t_shell *shell);

/** MINISHELL FUNC **/
void				minishell(t_shell *shell, t_env *env);

/** PRINT FUNC **/
void				print_msg_err(char *cmd, char *err_cmd, char *msg);
void				print_std_no_nl(char *msg);
void				print_std(char *msg);
void				print_err(char *msg);

/** SYNTAX FUNC **/
void				syntax_minishell_cmd(t_token **tokens, int *i, int *rc);

/** TOKENIZER FUNC **/
t_token				*get_new_token(int type, int subtype, char *str);
t_token				**tokenize(char *string);

/** TREE CMD FUNC **/
t_node				*tree_minishell_cmd(t_token **tokens, int *i, t_env *env);

/** TREE FUNC **/
t_node				*get_new_node(int type, int subtype, t_data *data);
t_node				*tree_redirects(t_token **tokens, int *i, t_env *env,
						int subtype);
t_node				*build_tree(t_token **tokens, t_env *env);
void				free_tree(t_node *node);

/** UTILS FUNC **/
int					count_words(char *string);

#endif
