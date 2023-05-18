/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:01 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/19 01:43:51 by fgeorgea         ###   ########.fr       */
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
}


// Closes all useless pipes in the children.
void	close_pipes_children(size_t pos, t_pipex *p)
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
