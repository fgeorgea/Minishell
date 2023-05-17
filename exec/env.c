/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:24:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/17 23:49:38 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ft_free(env->value);
	env->value = tmp;
}

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
			ft_free(tmp);
			ft_free_array_pos((void **)array, i);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		ft_free(tmp);
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
}

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
