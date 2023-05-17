/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:34:14 by mle-biha          #+#    #+#             */
/*   Updated: 2023/05/17 11:37:34 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env_value(t_env *env, char *key)
{
	env = get_env(env, key);
	if (env != NULL)
		return (env->value);
	return (NULL);
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
