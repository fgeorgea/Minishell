/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/18 14:46:07 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	children(size_t pos, t_cmd *cmd, t_pipex *p)
{
	set_signals(CHILD);
	g_sh->is_child = CHILD;
	p->infile = open_infile(cmd);
	if (g_sh->here_doc_status)
		exit(EXIT_SUCCESS);
	p->outfile = open_outfile(cmd);
	close_pipes_children(pos, p);
	if (pos == 0)
		first_child(p);
	else if (pos == p->nbr_pipe)
		last_child(pos, p);
	else
		middle_child(pos, p);
	check_cmd(cmd->cmd);
	ft_execve(cmd->cmd, p->env_array);
}

void	exec_cmds(void)
{
	size_t	i;
	t_pipex	*p;
	t_cmd	*cmd;

	i = 0;
	p = g_sh->pipex;
	cmd = g_sh->cmd;
	if (check_builtins_n_missing_path(p, cmd))
		return ;
	update_last_cmd((const char**)cmd->cmd);
	while (cmd)
	{
		ft_pipe(i);
		if (!ft_fork(i))
			return ;
		if (p->pids[i] == 0)
			children(i, cmd, p);
		else
			set_signals(PARENT);
		close_pipes_parent(i, p);
		cmd = cmd->next;
		i++;
	}
}
