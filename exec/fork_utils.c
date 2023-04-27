/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/27 14:27:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parent_close(int pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	if (pos == 0)
	{
		//ft_close(&p->infile);
		ft_close(&p->pipefd[0][1]);
	}
	else if (pos == p->nbr_fork - 1)
	{
		ft_close(&p->pipefd[pos - 1][0]);
		//ft_close(&p->outfile);
	}
	else
	{
		ft_close(&p->pipefd[pos - 1][0]);
		ft_close(&p->pipefd[pos][1]);
	}
}
