/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:01 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/09 12:13:13 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes_children(int pos, t_pipex *p)
{
	if (pos == 0 && p->nbr_pipe > 0)
		ft_close(&p->pipefd[0][0]);
	if (pos == 0 && p->outfile > 0 && p->nbr_pipe > 0)
		ft_close(&p->pipefd[0][1]);
	if (pos == p->nbr_pipe && p->nbr_pipe > 0 && p->infile > 0)
		ft_close(&p->pipefd[pos - 1][0]);
	if (pos < p->nbr_pipe && pos > 0 && p->infile > 0)
		ft_close(&p->pipefd[pos - 1][0]);
	if (pos < p->nbr_pipe && pos > 0 && p->outfile > 0)
		ft_close(&p->pipefd[pos][1]);
}

static void	close_first_child(t_pipex *p)
{
	if (p->infile > 0)
		ft_close(&p->infile);
	if (p->outfile > 0)
		ft_close(&p->outfile);
	else if (p->nbr_pipe > 0)
		ft_close(&p->pipefd[0][1]);
}

static void	close_last_child(t_pipex *p)
{
	if (p->infile > 0)
		ft_close(&p->infile);
	else
		ft_close(&p->pipefd[p->nbr_pipe - 1][0]);
	if (p->outfile > 0)
		ft_close(&p->outfile);
}

static void	close_middle_child(int pos, t_pipex *p)
{
	if (p->infile > 0)
		ft_close(&p->infile);
	else
		ft_close(&p->pipefd[pos - 1][0]);
	if (p->outfile > 0)
		ft_close(&p->outfile);
	else
		ft_close(&p->pipefd[pos][1]);
}

void	close_pipes_parent(int pos, t_pipex *p)
{
	if (pos == 0)
		close_first_child(p);
	else if (pos > 0 && pos == p->nbr_pipe)
		close_last_child(p);
	else if (pos > 0 && pos < p->nbr_pipe)
		close_middle_child(pos, p);
}