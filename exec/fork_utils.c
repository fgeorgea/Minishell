/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:01:40 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parent_close(int pos, t_pipex *p)
{
	if (pos == 0)
	{
		ft_close(&p->infile, p);
		ft_close(&p->pipefd[0][1], p);
	}
	else if (pos == p->nbr_fork - 1)
	{
		ft_close(&p->pipefd[pos - 1][0], p);
		ft_close(&p->outfile, p);
	}
	else
	{
		ft_close(&p->pipefd[pos - 1][0], p);
		ft_close(&p->pipefd[pos][1], p);
	}
}
