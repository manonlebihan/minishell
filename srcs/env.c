/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:07:08 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/16 16:54:46 by mle-biha         ###   ########.fr       */
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
	if (env != NULL) {
		env->key = ft_strdup(key); // check malloc
		if (value == NULL)
			env->value = ft_strdup(""); // check malloc
		else
			env->value = ft_strdup(value); // check malloc
		env->next = NULL;
	}
	return (env);
}

t_env	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
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

char	*get_env_value(t_env *env, char *key)
{
	env = get_env(env, key);
	if (env != NULL)
		return env->value;
	return (NULL);
}

void	add_env_value(t_env *env, char *key, char *value)
{
	t_env	*an_env;

	an_env = get_env(env, key);
	if (an_env != NULL)
	{
		free(an_env->value);
		an_env->value = ft_strdup(value); // check malloc
		return;
	}
	while (env->next)
		env = env->next;
	env->next = create_env(key, value);
}

char	**get_env_array(t_env *env)
{
	char	**array;
	t_env	*tmp;
	int		var_nb;
	int		i;

	var_nb = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, ENV_INIT))
			var_nb++;
		tmp = tmp->next;
	}
	array = (char **)malloc(var_nb * sizeof(char *) + 1); // check malloc
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, ENV_INIT))
			array[i] = ft_strjoin(tmp->key, ft_strjoin("=", tmp->value)); // check malloc
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}