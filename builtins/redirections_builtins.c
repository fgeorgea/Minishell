/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:06:31 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/17 17:54:12 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_redir	*get_in_redir_builtin(t_redir **redirection)
{
	t_redir	*redir;
	t_redir	*last;

	if (!redirection || !*redirection)
		return (NULL);
	redir = *redirection;
	last = NULL;
	while (redir)
	{
		if (redir->mode == HEREDOC)
			here_doc(redir->key);
		if (redir->mode == HEREDOC_EXP)
			ft_here_doc_exp(redir->key);
		if (redir->mode == IN && !file_exist(redir->key))
			return (redir);
		if (redir->mode == HEREDOC || redir->mode == IN || redir->mode == HEREDOC_EXP)
			last = redir;
		redir = redir->next;
		if (g_sh->here_doc_status)
			return (0);
	}
	return (last);
}

static int	get_infile_builtin(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = get_in_redir_builtin(&cmd->redir);
	if (!redir || !redir->key)
		return (0);
	if (!file_exist(redir->key) && redir->mode == IN)
	{
		print_err(NULL, redir->key, ": file not found\n");
		g_sh->pipe_exit = 1;
		return (-1);
	}
	if (redir->mode == IN)
		fd = ft_open(redir->key, IN_FLAGS, -1);
	else
		fd = ft_open(TMP_FILE, IN_FLAGS, -1);
	return (fd);
}

int	builtin_redirection(void)
{
	t_pipex	*p;
	t_cmd	*cmd;

	p = g_sh->pipex;
	if (p->nbr_cmds > 1)
		return (1);
	cmd = g_sh->cmd;
	p->infile = get_infile_builtin(cmd);
	if (p->infile == -1)
		return (0);
	if (p->infile > 0)
		ft_close(&p->infile);
	p->outfile = open_outfile(cmd);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	return (1);
}

int	ft_dup(int fildes)
{
	int	dup_stdout;

	if (g_sh->pipex->nbr_cmds > 1)
		return (-2);
	dup_stdout = dup(fildes);
	if (dup_stdout == -1)
		ft_exit(EXIT_DUP_FAILURE);
	return (dup_stdout);
}

void	restore_stdout(int dup_stdout)
{
	if (g_sh->pipex->nbr_cmds > 1)
		return ;
	if (close(STDOUT_FILENO) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	link_files(dup_stdout, STDOUT_FILENO);
}
