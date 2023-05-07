/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:11:20 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/07 18:18:19 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	int		i;
	char	**env;

	if (!g_sh->env)
		return ;
	i = 0;
	env = g_sh->pipex->env_array;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
