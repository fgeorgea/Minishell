/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/25 14:32:51 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipex(int argc, char **argv, char **env)
{
	ft_init_struct(argc, argv);
	ft_parse_cmds();
	ft_here_doc();
	ft_exec(env);
	ft_waitpid();
	// ft_free_array(g.paths);
	// free(g.pids);
	// ft_free_int_array(g.pipefd, g.nbr_pipe);
	// ft_lstclear_pipex(&g.lst);
	ft_unlink_tmp();	
}
