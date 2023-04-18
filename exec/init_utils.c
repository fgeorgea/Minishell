/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:27:39 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/18 17:36:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_here_doc(int argc, char **argv, t_global *g)
{
	if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (ft_strlen(argv[1]) == 8))
		g->is_heredoc = 1;
	if (g->is_heredoc && (argc < 6))
		ft_error(g, "Program executes here_doc but does not have enough args\n");
}

static void	ft_init_heredoc(char **argv, t_global *g)
{
	g->nbr_cmds = g->argc - 4;
	g->nbr_pipe = g->nbr_cmds - 1;
	g->nbr_fork = g->nbr_cmds;
	g->end_token = argv[2];
	g->infile = open(TMP_FILE, O_WRONLY | O_CREAT, 0644);
	if (g->infile == -1)
		ft_error(g, "Failed to open infile of here_doc\n");
}

void	ft_init_struct_vars(int argc, char **argv, t_global *g)
{
	g->paths = NULL;
	g->lst = NULL;
	g->pids = NULL;
	g->pipefd = NULL;
	g->end_token = NULL;
	g->argc = argc;
	g->nbr_cmds = g->argc - 3;
	g->nbr_pipe = g->nbr_cmds - 1;
	g->nbr_fork = g->nbr_cmds;
	g->outfile = open(argv[g->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (g->outfile == -1)
		ft_error(g, "Failed to open outfile\n");
	if (g->is_heredoc)
		ft_init_heredoc(argv, g);
	else
	{
		g->infile = open(argv[1], O_RDONLY);
		if (g->infile == -1)
			ft_error(g, argv[1]);
	}
}
