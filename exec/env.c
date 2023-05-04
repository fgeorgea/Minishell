/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:24:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/04 15:40:18 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(char *key, char *new_value)
{
	t_env	*env;
	char	*tmp;
	
	env = get_env_struct(key, ft_strlen(key));
	if (!env)
		return ;
	tmp = ft_strdup(new_value);
	if (!tmp)
		ft_exit(EXIT_MALLOC_FAILURE);
	if (env->value)
		free(env->value);
	env->value = tmp;
}

t_env	*get_env_struct(char *needle, int size)
{
	t_env	*env;

	env = g_sh->env;
	while (env)
	{
		if (ft_strlen(needle) == ft_strlen(env->key)
			&& ft_strncmp(needle, env->key, size) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(char *key_to_find, int size)
{
	t_env	*env;

	env = g_sh->env;
	while (env)
	{
		if (ft_strlen(key_to_find) == ft_strlen(env->key)
			&& ft_strncmp(key_to_find, env->key, size) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	join_key_value(t_env *lst, char **array)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	while (lst)
	{
		tmp = ft_strjoin(lst->key, "=");
		if (!tmp)
			return (-1);
		array[i] = ft_strjoin(tmp, lst->value);
		if (!array[i])
			return (-1);
		free(tmp);
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (1);
}

void	lst_to_array(t_env **lst)
{
	int		i;
	char	**array;
	int		lstsize;
	t_env	*tmp;

	if (!lst)
		return ;
	i = 0;
	lstsize = lstsize_env(lst);
	tmp = *lst;
	array = malloc(sizeof(char *) * (lstsize + 1));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	if (!join_key_value(tmp, array))
	{
		ft_free_array(array);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	if (g_sh->pipex->env_array)
		ft_free_array(g_sh->pipex->env_array);
	g_sh->pipex->env_array = array;
}
