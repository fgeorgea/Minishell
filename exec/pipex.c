/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/28 03:29:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipex(void)
{
	g_sh->pipex = malloc(sizeof(t_pipex));
	if (!g_sh->pipex)
		ft_exit(EXIT_MALLOC_FAILURE);
	ft_init_struct();
	ft_exec();
	ft_waitpid();
	ft_free_pipex();
	ft_free_pipex();
}
