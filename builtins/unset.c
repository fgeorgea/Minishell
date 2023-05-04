/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:29:11 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/04 15:43:00 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_var_env(char *var)
{
	t_env	*env;
	t_env	*previous;
	
	env = g_sh->env;
	previous = NULL;
	if (!get_env_value(var, ft_strlen(var)))
		return ;
	while (env->next && env->next->key != var)
		env = env->next;
	if (!env->next)
		return ;
	previous = env;
	env = env->next;
	previous->next = env->next;
	free(env->key);
	free(env->value);
}

void	ft_unset(char **vars)
{
	int	i;

	i = 0;
	if (!vars)
		return ;
	while (vars[i])
	{
		delete_var_env(vars[i]);
		i++;
	}
	lst_to_array(&g_sh->env);
}
