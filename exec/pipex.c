/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:55:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/18 17:42:58 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_global	g;

// 	if (argc >= 5)
// 	{
// 		ft_init_struct(argc, argv, env, &g);
// 		ft_parse_cmds(&g);
// 		if (g.is_heredoc)
// 			ft_here_doc(&g);
// 		ft_exec(env, &g);
// 		ft_waitpid(&g);
// 		ft_free_array(g.paths);
// 		free(g.pids);
// 		ft_free_int_array(g.pipefd, g.nbr_pipe);
// 		ft_lstclear_pipex(&g.lst);
// 		ft_unlink_tmp();
// 	}
// 	return (0);
// }
