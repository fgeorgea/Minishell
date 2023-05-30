/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:01 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/30 17:39:41 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Closes all useless pipes in the parent after the children.
void	close_pipes_parent(size_t pos, t_pipex *p)
{
	if (p->infile > 0)
		ft_close(&p->infile);
	if (p->outfile > 0)
		ft_close(&p->outfile);
	if (p->nbr_pipe <= 0)
		return ;
	if (pos == 0)
		ft_close(&p->pipefd[0][1]);
	else if (pos > 0 && pos == p->nbr_pipe)
		ft_close(&p->pipefd[p->nbr_pipe - 1][0]);
	else if (pos > 0 && pos < p->nbr_pipe)
	{
		ft_close(&p->pipefd[pos - 1][0]);
		ft_close(&p->pipefd[pos][1]);
	}
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
