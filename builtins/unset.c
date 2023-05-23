/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:29:11 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/23 13:46:41 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_key(const char *key)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
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
	if (!get_env_struct(var))
		return ;
	if (compare_keys(var, env->key))
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
		if (is_valid_key(vars[i]) && !compare_keys(vars[i], "_"))
			delete_var_env(vars[i]);
		if (!is_valid_key(vars[i]))
			print_err("unset: `", (char *)vars[i], NAVI, 1);
		i++;
	}
	lst_to_array(&g_sh->env);
}
