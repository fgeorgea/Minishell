/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:08:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/21 20:26:58 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_free(env->value);
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
