/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 03:02:11 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Sets up the correct signals and exits if there are no cmd or error...
static void	prepare_child(size_t pos, t_cmd *cmd, t_pipex *p)
{
	set_signals(CHILD);
	g_sh->is_child = CHILD;
	if (p->infile < 0 || p->outfile < 0 || g_sh->here_doc_status || !cmd->cmd)
		exit_only_child(g_sh->pipe_exit);
	close_pipes_children(pos, p);
}

// All the child execution goes in here.
static void	children(size_t pos, t_cmd *cmd, t_pipex *p)
{
	prepare_child(pos, cmd, p);
	if (pos == 0)
		first_child(p);
	else if (pos == p->nbr_pipe)
		last_child(pos, p);
	else
		middle_child(pos, p);
	check_cmd(cmd->cmd);
	if (p->hd_tmp)
		unlink(p->hd_tmp);
	ft_free((void **)&p->hd_tmp);
	ft_execve(cmd->cmd, p->env_array);
}

// This function is the main execution LOOP.
void	exec_cmds(t_pipex *p, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (is_single_builtin())
		return ;
	update_last_cmd((const char **)cmd->cmd);
	while (cmd)
	{
		set_lst_cmd(i);
		setup_heredoc(cmd->redir, i);
		if (g_sh->here_doc_status)
			break ;
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
