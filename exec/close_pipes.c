/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:01 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/25 16:02:16 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	close_middle_child(size_t pos, t_pipex *p)
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

// Closes all useless pipes in the parent after the children.
void	close_pipes_parent(size_t pos, t_pipex *p)
{
	if (pos == 0)
		close_first_child(p);
	else if (pos > 0 && pos == p->nbr_pipe)
		close_last_child(p);
	else if (pos > 0 && pos < p->nbr_pipe)
		close_middle_child(pos, p);
	if (p->infile)
		ft_close(&p->infile);
	if (p->outfile)
		ft_close(&p->outfile);
}

// Closes all useless pipes in the children.
void	close_pipes_children(size_t pos, t_pipex *p)
{
	if (p->nbr_pipe <= 0)
		return ;
	if (pos == 0)
		ft_close(&p->pipefd[0][0]);
	if (pos == 0 && p->outfile > 0)
		ft_close(&p->pipefd[0][1]);
	if (pos == p->nbr_pipe && p->infile > 0)
		ft_close(&p->pipefd[pos - 1][0]);
	if (pos < p->nbr_pipe && pos > 0)
		ft_close(&p->pipefd[pos][0]);
	if (pos < p->nbr_pipe && pos > 0 && p->infile > 0)
		ft_close(&p->pipefd[pos - 1][0]);
	if (pos < p->nbr_pipe && pos > 0 && p->outfile > 0)
		ft_close(&p->pipefd[pos][1]);
}
