/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:11:20 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/01 22:17:16 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Prints the env linked lst.
void	env_builtin(const char **arg)
{
	t_env	*env;

	env = g_sh->env;
	if (arraylen(arg) > 0)
	{
		print_err((char *)arg[0], NSFOD, NULL, 127);
		return ;
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
