/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/01 16:30:36 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_signal(int EXIT_MACRO)
{
	if (EXIT_MACRO != 0)
		ft_exit(EXIT_MACRO);
}

void	ft_parent_close(int pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	check_exit_signal(p->exit_macro);
	ft_close(&p->infile);
	ft_close(&p->outfile);
	if (pos == 0)
		ft_close(&p->pipefd[0][1]);
	else if (pos == p->nbr_fork - 1)
		ft_close(&p->pipefd[pos - 1][0]);
	else
	{
		ft_close(&p->pipefd[pos - 1][0]);
		ft_close(&p->pipefd[pos][1]);
	}
}
