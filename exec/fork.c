/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 17:26:59 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork(int pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	p->pids[pos] = fork();
	if (p->pids[pos] == -1)
		ft_exit(EXIT_FORK_FAILURE);
}

pid_t	*ft_createfork_array(t_pipex *p)
{
	pid_t	*array;

	array = malloc(sizeof(pid_t) * (p->nbr_fork));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	return (array);
}

void	ft_first_child(t_pipex *p)
{
	if (p->infile > 0)
		link_files(p->infile, STDIN_FILENO);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	else if (p->nbr_pipe != 0)
		link_files(p->pipefd[0][1], STDOUT_FILENO);
}

void	ft_last_child(int pos, t_pipex *p)
{
	if (p->infile > 0)
		link_files(p->infile, STDIN_FILENO);
	else
		link_files(p->pipefd[pos - 1][0], STDIN_FILENO);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
}

void	ft_middle_child(int pos, t_pipex *p)
{
	if (p->infile > 0)
		link_files(p->infile, STDIN_FILENO);
	else
		link_files(p->pipefd[pos - 1][0], STDIN_FILENO);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	else
		link_files(p->pipefd[pos][1], STDOUT_FILENO);
}
