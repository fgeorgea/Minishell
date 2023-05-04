/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:37:16 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/04 15:42:49 by fgeorgea         ###   ########.fr       */
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

void	sort_env_ascii(void)
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
	lst_to_array(&g_sh->env);
}