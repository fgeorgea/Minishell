/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 18:32:21 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This function is the main pipeline for the execution.
void	ft_pipex(void)
{
	g_sh->pipex = malloc(sizeof(t_pipex));
	if (!g_sh->pipex)
		ft_exit(EXIT_MALLOC_FAILURE);
	init_struct_pipex();
	exec_cmds(g_sh->pipex, g_sh->cmd);
	ft_waitpid();
	free_pipex();
}
