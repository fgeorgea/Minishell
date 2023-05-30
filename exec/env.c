/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:24:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/30 15:44:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Replaces a value paired with a key in the env.
void	change_env_value(const char *key, const char *new_value)
{
	t_env	*env;
	char	*tmp;

	tmp = NULL;
	env = get_env_struct(key);
	if (!env)
		return ;
	if (new_value)
	{
		tmp = ft_strdup(new_value);
		if (!tmp)
			ft_exit(EXIT_MALLOC_FAILURE);
	}
	ft_free((void **)&env->value);
	env->value = tmp;
}

// Returns a reference to a specific node based on a given key.
t_env	*get_env_struct(const char *key)
{
	t_env	*env;

	env = g_sh->env;
	while (env)
	{
		if (compare_keys(key, env->key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

// Returns the value paired with the given key in the env.
char	*get_env_value(const char *key)
{
	t_env	*env;

	env = g_sh->env;
	while (env)
	{
		if (compare_keys(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	join_key_value(t_env *lst, char **array)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (lst)
	{
		tmp = ft_strjoin(lst->key, "=");
		array[i] = ft_strjoin(tmp, lst->value);
		if (!array[i])
		{
			ft_free((void **)&tmp);
			ft_free_array_pos((void **)array, i);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		ft_free((void **)&tmp);
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
}

// Converts the env linked list to an array of strings.
void	lst_to_array(t_env **lst)
{
	char	**array;
	int		lstsize;
	t_env	*env;

	lstsize = lstsize_env(lst);
	env = *lst;
	ft_free_array(g_sh->pipex->env_array);
	array = malloc(sizeof(char *) * (lstsize + 1));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	join_key_value(env, array);
	g_sh->pipex->env_array = array;
}
