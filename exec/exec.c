/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/26 14:58:35 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// All the child execution goes in here.
static void	children(size_t pos, t_cmd *cmd, t_pipex *p)
{
	set_signals(CHILD);
	g_sh->is_child = CHILD;
	if (p->infile < 0 || p->outfile < 0)
		exit(1);
	if (g_sh->here_doc_status)
		exit(0);
	close_pipes_children(pos, p);
	if (pos == 0)
		first_child(p);
	else if (pos == p->nbr_pipe)
		last_child(pos, p);
	else
		middle_child(pos, p);
	if (!cmd->cmd)
		exit(EXIT_SUCCESS);
	if (!cmd->cmd)
		exit(0);
	check_cmd(cmd->cmd);
	ft_execve(cmd->cmd, p->env_array);
}

// This function is the main execution LOOP.
void	exec_cmds(void)
{
	size_t	i;
	t_pipex	*p;
	t_cmd	*cmd;

	i = 0;
	p = g_sh->pipex;
	cmd = g_sh->cmd;
	if (check_builtins(p, cmd))
		return ;
	update_last_cmd((const char **)cmd->cmd);
	while (cmd)
	{
		set_lst_cmd(i);
		ft_pipe(i);
		setup_redir(cmd->redir, p);
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
