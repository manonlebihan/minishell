/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:07:08 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/22 19:37:40 by mle-biha         ###   ########.fr       */
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

	env = (t_env *)ft_calloc(1, sizeof(t_env)); // OK
	if (env != NULL)
	{
		env->key = ft_strdup(key); // OK
		if (env->key == NULL)
			return (NULL);
		if (value == NULL)
		{
			env->value = ft_strdup(""); // OK
			if (env->value == NULL)
				return (NULL);
		}
		else
		{
			env->value = ft_strdup(value); // OK
			if (env->value == NULL)
				return (NULL);
		}
		env->next = NULL;
	}
	return (env);
}

void	list_env_value(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, ENV_INIT))
		{
			print_std_no_nl(env->key);
			print_std_no_nl("=");
			print_std(env->value);
		}
		env = env->next;
	}
}

int	add_env_value(t_env *env, char *key, char *value)
{
	t_env	*an_env;

	an_env = get_env(env, key);
	if (an_env != NULL)
	{
		free(an_env->value);
		an_env->value = ft_strdup(value); // check malloc
		if (an_env->value == NULL)
			return (1);
		return (0);
	}
	while (env->next)
		env = env->next;
	env->next = create_env(key, value); // check malloc
	if (env->next == NULL)
		return (1);
	return (0);
}
