/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:06:31 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/21 17:57:47 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns a reference to the last OUT redir.
	Returns NULL if there are no OUT redir.
*/
static t_redir	*get_out_redir_builtin(t_redir **redirection)
{
	t_redir	*redir;
	t_redir	*last;

	if (!redirection || !*redirection)
		return (NULL);
	redir = *redirection;
	last = NULL;
	while (redir)
	{
		if (redir->mode == OUT || redir->mode == OUT_APP)
		{
			if (!test_redir_open(redir->key, redir->mode, 0644))
				return (redir);
		}
		if ((redir->mode == OUT || redir->mode == OUT_APP))
			last = redir;
		redir = redir->next;
	}
	return (last);
}

/*
	Opens the outfile and returns the file descriptor.
	Returns 0 if there is no redir.
	Returns -1 if there is an issue opening the redir file.
*/
static int	open_outfile_builtin(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = get_out_redir_builtin(&cmd->redir);
	if (!redir)
		return (0);
	fd = ft_open_redir(redir->key, redir->mode, 0644);
	return (fd);
}

/*
	Opens every heredoc if there are any.
	Returns the last IN redir.
	Returns NULL if there is no IN redir.
	'!' ->exits if there is a non existing infile input.
*/
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
		if (redir->mode == IN)
		{
			if (!test_redir_open(redir->key, IN, 0644))
				return (redir);
		}
		if (redir->mode == HEREDOC || redir->mode == IN || redir->mode == HEREDOC_EXP)
			last = redir;
		redir = redir->next;
		if (g_sh->here_doc_status)
			return (NULL);
	}
	return (last);
}

/*
	Opens the eventual infile.
	Returns the infile fd.
	Return 0 if there is no IN redir.
	'!' -> exits if the file does not exist.
*/
static int	open_infile_builtin(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = get_in_redir_builtin(&cmd->redir);
	if (!redir || !redir->key)
		return (0);
	fd = ft_open_redir(redir->key, redir->mode, 0644);
	return (fd);
}

// Set up redirection for single builtin cmd.
int	builtin_redirection(void)
{
	t_pipex	*p;
	t_cmd	*cmd;

	p = g_sh->pipex;
	if (p->nbr_fork > 0)
		return (1);
	cmd = g_sh->cmd;
	p->infile = open_infile_builtin(cmd);
	if (p->infile == -1)
		return (0);
	ft_close(&p->infile);
	p->outfile = open_outfile_builtin(cmd);
	if (p->outfile == -1)
		return (0);
	else if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	return (1);
}
