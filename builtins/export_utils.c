/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:37:16 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/24 13:31:59 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_values_app(char *key, char *s1, char *s2)
{
	char	*join_value;

	join_value = ft_strjoin(s1, s2);
	if (!join_value)
	{
		ft_free(key);
		ft_free(s2);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	change_env_value(key, join_value);
	ft_free(join_value);
}

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

// Sorts the env array in ascii order with the keys.
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

/*
	Prints the env like so: key="value"
	'!' -> If a value is set to NULL, it will only print 'key='
*/
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
