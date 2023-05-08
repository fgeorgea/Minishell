/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 17:53:48 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_pipes(int pos, t_pipex *p)
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

void	check_exit_signal(int EXIT_MACRO)
{
	if (EXIT_MACRO != 0)
		ft_exit(EXIT_MACRO);
}

void	ft_parent_close(int pos, t_pipex *p)
{
	if (pos == 0)
	{
		if (p->infile > 0)
			ft_close(&p->infile);
		if (p->outfile > 0)
			ft_close(&p->outfile);
		else if (p->nbr_pipe > 0)
			ft_close(&p->pipefd[0][1]);
	}
	if (pos == p->nbr_pipe && pos != 0)
	{
		if (p->infile > 0)
			ft_close(&p->infile);
		else
			ft_close(&p->pipefd[pos - 1][0]);
		if (p->outfile > 0)
			ft_close(&p->outfile);
	}
	if (pos > 0 && pos < p->nbr_pipe)
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
}

void	link_files(int fildes, int fildes2)
{
	ft_dup2(fildes, fildes2);
	ft_close(&fildes);
}