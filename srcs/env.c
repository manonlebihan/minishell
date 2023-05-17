/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:07:08 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/17 11:34:49 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(void)
{
	return (create_env(ENV_INIT, ""));
}

t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)ft_calloc(1, sizeof(t_env)); // check malloc
	if (env != NULL)
	{
		env->key = ft_strdup(key); // check malloc
		if (value == NULL)
			env->value = ft_strdup(""); // check malloc
		else
			env->value = ft_strdup(value); // check malloc
		env->next = NULL;
	}
	return (env);
}

void	list_env_value(t_env *env)
{
	char	*env_var;

	while (env)
	{
		env_var = ft_strjoin(ft_strjoin(env->key, "="), env->value); // check malloc
		if (ft_strcmp(env->key, ENV_INIT))
			print_std(env_var);
		env = env->next;
		free(env_var);
	}
}

void	add_env_value(t_env *env, char *key, char *value)
{
	t_env	*an_env;

	an_env = get_env(env, key);
	if (an_env != NULL)
	{
		free(an_env->value);
		an_env->value = ft_strdup(value); // check malloc
		return ;
	}
	while (env->next)
		env = env->next;
	env->next = create_env(key, value);
}
