/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:45:56 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 16:47:57 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(char **env)
{
	int		i;
	int		j;
	t_env	*new_node;
	char	*key;
	char	*value;

	i = 0;
	while (env && env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		key = ft_strndup(env[i], j);
		value = ft_strdup(&env[i][j + 1]);
		if (!value)
			ft_free((void **)&key);
		new_node = ft_lstnew_env(key, value);
		if (!new_node)
			ft_exit(EXIT_MALLOC_FAILURE);
		ft_lstadd_back_env(&g_sh->env, new_node);
		i++;
	}
}

void	init_oldpwd(void)
{
	t_env	*oldpwd;

	oldpwd = get_env_struct("OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = NULL;
	}
	else
	{
		oldpwd = ft_calloc(1, sizeof(t_env));
		if (!oldpwd)
			ft_exit(EXIT_MALLOC_FAILURE);
		oldpwd->key = ft_strdup("OLDPWD");
		ft_lstadd_back_env(&g_sh->env, oldpwd);
		if (!oldpwd->key)
			ft_exit(EXIT_MALLOC_FAILURE);
	}
}

void	if_env_not_set(void)
{
	char	*key;
	char	*value;
	t_env	*new_node;

	if (!get_env_struct("_"))
	{
		key = ft_strdup("_");
		value = ft_strdup("minishell");
		new_node = ft_lstnew_env(key, value);
		if (!new_node)
			ft_exit(EXIT_MALLOC_FAILURE);
		ft_lstadd_back_env(&g_sh->env, new_node);
	}
	if (!get_env_struct("PWD"))
	{
		key = ft_strdup("PWD");
		value = getcwd(NULL, 0);
		new_node = ft_lstnew_env(key, value);
		if (!new_node)
			ft_exit(EXIT_MALLOC_FAILURE);
		ft_lstadd_back_env(&g_sh->env, new_node);
	}
}

void	create_sh_lvl(void)
{
	t_env	*new_node;
	char	*key;
	char	*value;

	key = ft_strdup("SHLVL");
	value = ft_strdup("1");
	new_node = ft_lstnew_env(key, value);
	if (!new_node)
		ft_exit(EXIT_MALLOC_FAILURE);
	ft_lstadd_back_env(&g_sh->env, new_node);
}

void	init_shell_lvl(void)
{
	t_env	*env;
	int		v;

	env = g_sh->env;
	while (env)
	{
		if (compare_keys(env->key, "SHLVL"))
		{
			v = ft_atoi(env->value);
			ft_free((void **)&env->value);
			if (v < 0 || v >= 1000)
				env->value = ft_strdup("0");
			else if (v == 999)
				env->value = ft_strdup("");
			else
				env->value = ft_itoa(v + 1);
			if (!env->value)
				ft_exit(EXIT_MALLOC_FAILURE);
			return ;
		}
		env = env->next;
	}
}
