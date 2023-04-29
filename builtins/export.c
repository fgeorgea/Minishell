/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:54:57 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 02:32:38 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(void)
{
    int     i;
	char    **env;

    i = 0;
    env = g_sh->pipex->env_array;
    while (env[i])
    {
        printf("declare -x %s\n", env[i]);
        i++;
    }
}