/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:06:31 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 18:25:39 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Set up redirection for single builtin cmd.
int	builtin_redirection(void)
{
	t_pipex	*p;
	t_cmd	*cmd;

	p = g_sh->pipex;
	if (p->nbr_fork > 0)
		return (1);
	cmd = g_sh->cmd;
	setup_heredoc(cmd->redir, 0);
	if (g_sh->here_doc_status)
		return (0);
	setup_redir(cmd->redir, p);
	if (p->infile < 0 || p->outfile < 0)
		return (0);
	if (p->infile > 0)
		ft_close(&p->infile);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	return (1);
}
