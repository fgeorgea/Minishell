/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:54:57 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/10 13:48:10 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_export(char *str)
{
	int	i;
	int	len;

	len = 0;
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[len] && (str[len] != '=' && str[len] != '+'))
		len++;
	if (!str[len] || (str[len] == '+' && str[len + 1] != '='))
		return (0);
	i = 0;
	while (i < len)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}


static void	add_var_to_env_app(char *str, int pos)
{
	t_env	*env;
	char	*key;
	char	*value;
	char	*old_value;
	
	key = ft_substr(str, 0, pos - 2);
	value = ft_strdup(&str[pos + 1]);
	env = get_env_struct(key, ft_strlen(key));
	if (!env)
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
		return ;
	}
	if (!env->value)
		env->value = value;
	else
	{
		old_value = ft_strdup(env->value);
		free(env->value);
		env->value = ft_strjoin(old_value, value);
	}
	free(key);
}

static void	add_var_to_env(char *str, int pos)
{
	t_env	*env;
	char	*key;
	char	*value;

	key = ft_substr(str, 0, pos);
	value = ft_strdup(&str[pos + 1]);
	env = get_env_struct(key, ft_strlen(key));
	if (!env)
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
		return ;
	}
	change_env_value(key, value);
}

static void	check_append(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		add_var_to_env_app(str, i);
	else
		add_var_to_env(str, i);
}

void	ft_export(char **strs)
{
    int     i;
	char    **env;
	
    i = 0;
	env = NULL;
	if (!*strs)
	{
		sort_env_ascii();
		env = g_sh->pipex->env_array;
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
		return ;
	}
	while (strs[i])
	{
		if (check_valid_export(strs[i]))
			check_append(strs[i]);
		i++;
	}
	lst_to_array(&g_sh->env);
}
