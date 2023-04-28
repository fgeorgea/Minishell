/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/28 03:29:07 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child(int pos, t_cmd *cmd, t_pipex *p)
{
	ft_here_doc();
	if (pos == 0)
		ft_first_child(cmd, p);
	else if (pos == p->nbr_fork - 1)
		ft_last_child(pos, cmd, p);
	else
		ft_middle_child(pos, cmd, p);
}

void	ft_exec(void)
{
	t_pipex	*p;
	t_cmd	*cmd;
	int		i;

	i = 0;
	p = g_sh->pipex;
	cmd = g_sh->cmd;
	while (cmd)
	{
		ft_pipe(i);
		ft_fork(i);
		if (p->pids[i] == 0)
			ft_child(i, cmd, p);
		ft_parent_close(i);
		cmd = cmd->next;
		i++;
	}
}
