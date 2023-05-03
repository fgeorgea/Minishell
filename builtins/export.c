/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:54:57 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/03 14:36:10 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

static void	sort_env_ascii(void)
{
	t_env	*env;
	char	*tmp;

	env = g_sh->env;
	while (env->next)
	{
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			tmp = env->key;
			env->key = env->next->key;
			env->next->key = tmp;
			env = g_sh->env;
		}
		else
			env = env->next;
	}
	ft_free_array(g_sh->pipex->env_array);
	g_sh->pipex->env_array = lst_to_array(&g_sh->env);
}

static int	check_valid_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_strnstr(str, "=", ft_strlen(str)) || !ft_isalpha(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	add_var_to_env(char *str)
{
	char	**var;
	char	*key;
	char	*value;
	
	
	var = ft_split_exit(str, '=');
	key = ft_strdup_exit(var[0]);
	value = ft_strdup_exit(var[1]);
	ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
	ft_free_array(var);
	ft_free_array(g_sh->pipex->env_array);
	g_sh->pipex->env_array = lst_to_array(g_sh->env);
}

void	ft_export(char **strs)
{
    int     i;
	char    **env;
	
    i = 0;
	env = NULL;
	if (!strs)
	{
		sort_env_ascii();
		env = g_sh->pipex->env_array;
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
	}
	while (strs[i])
	{
		if (check_valid_export(strs[i]))
			add_var_to_env(strs[i]);
		i++;
	}
}
