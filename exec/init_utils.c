/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:27:39 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/25 13:56:40 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_here_doc(int argc, char **argv, t_pipex *p)
{
	p->is_heredoc = 0;
	if ((ft_strncmp(argv[1], "here_doc", 8) == 0) && (ft_strlen(argv[1]) == 8))
		p->is_heredoc = 1;
	if (p->is_heredoc && (argc < 6))
		ft_error("Program executes here_doc but does not have enough args\n", 0);
}

static void	ft_init_heredoc(char **argv, t_pipex *p)
{
	p->nbr_cmds = p->argc - 4;
	p->nbr_pipe = p->nbr_cmds - 1;
	p->nbr_fork = p->nbr_cmds;
	p->end_token = argv[2];
	p->infile = open(TMP_FILE, O_WRONLY | O_CREAT, 0644);
	if (p->infile == -1)
		ft_error("Failed to open infile of here_doc\n", -1);
}

void	ft_init_struct_vars(int argc, char **argv, t_pipex *p)
{
	p->paths = NULL;
	p->lst = NULL;
	p->pids = NULL;
	p->pipefd = NULL;
	p->end_token = NULL;
	p->argc = argc;
	p->nbr_cmds = p->argc - 3;
	p->nbr_pipe = p->nbr_cmds - 1;
	p->nbr_fork = p->nbr_cmds;
	p->outfile = open(argv[p->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (p->outfile == -1)
		ft_error("Failed to open outfile\n", -1);
	if (p->is_heredoc)
		ft_init_heredoc(argv, p);
	else
	{
		p->infile = open(argv[1], O_RDONLY);
		if (p->infile == -1)
			ft_error(argv[1], 0);
	}
}
