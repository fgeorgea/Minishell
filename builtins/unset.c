/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:29:11 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/12 12:31:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_key(const char *key)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(key[0]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	delete_var_env(const char *var)
{
	t_env	*env;
	t_env	*previous;

	env = g_sh->env;
	if (!get_env_value(var))
		return ;
	if (compare_strucs(g_sh->env, env))
	{
		g_sh->env = g_sh->env->next;
		del_one_env(env);
		return ;
	}
	while (env->next)
	{
		if (compare_keys(env->next->key, var))
			break ;
		env = env->next;
	}
	if (!env->next)
		return ;
	previous = env;
	env = env->next;
	previous->next = env->next;
	del_one_env(env);
}

void	unset_builtin(const char **vars)
{
	size_t	i;

	i = 0;
	if (!vars || !*vars)
		return ;
	while (vars[i])
	{
		if (is_valid_key(vars[i]))
			delete_var_env(vars[i]);
		else
		{
			ft_putstr_fd("Minishell: unset: '", 2);
			ft_putstr_fd((char *)vars[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	lst_to_array(&g_sh->env);
}
