/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/26 17:44:11 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipex(int argc, char **argv)
{
	t_pipex	*p;
	
	g_sh->pipex = NULL;
	g_sh->pipex = malloc(sizeof(t_pipex));
	if (!g_sh->pipex)
		ft_error("Failed to malloc pipex struct\n", -1);
	p = g_sh->pipex;
	ft_init_struct(argc, argv);
	ft_parse_cmds();
	ft_here_doc();
	ft_exec();
	ft_waitpid();
	ft_free_array(p->paths);
	ft_free_array(p->env_array);
	free(p->pids);
	ft_free_int_array(p->pipefd, p->nbr_pipe);
	free(g_sh->pipex);
	ft_unlink_tmp();
}
