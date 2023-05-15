/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:37:16 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/15 12:37:17 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

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
	char	*tmp_key;
	char	*tmp_value;

	if (!g_sh->env)
		return ;
	env = g_sh->env;
	while (env->next)
	{
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			tmp_key = env->key;
			tmp_value = env->value;
			env->key = env->next->key;
			env->value = env->next->value;
			env->next->key = tmp_key;
			env->next->value = tmp_value;
			env = g_sh->env;
		}
		else
			env = env->next;
	}
	lst_to_array(&g_sh->env);
}

void	print_export(void)
{
	t_env	*env;

	if (!g_sh->env)
		return ;
	env = g_sh->env;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}
