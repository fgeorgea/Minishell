/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 02:29:49 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_heredoc(t_redir *redir)
{
	while (redir)
	{
		if (redir->mode == HEREDOC || redir->mode == HEREDOC_EXP)
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	setup_heredoc(t_redir *redirection, int pos)
{
	t_redir	*redir;

	if (!redirection)
		return ;
	if (!has_heredoc(redirection))
		return ;
	redir = redirection;
	create_hd_name(pos);
	g_sh->pipex->dup_stdin = dup(STDIN_FILENO);
	while (redir && !g_sh->here_doc_status)
	{
		if (redir->mode == HEREDOC)
			here_doc(redir->key);
		if (redir->mode == HEREDOC_EXP)
			ft_here_doc_exp(redir->key);
		redir = redir->next;
	}
	if (!g_sh->here_doc_status)
		restore_stdin(g_sh->pipex->dup_stdin);
	if (g_sh->here_doc_status)
		unlink_all_tmp();
}

static void	save_redir_fds(t_redir *last_in, t_redir *last_out)
{
	t_pipex	*p;

	p = g_sh->pipex;
	if (last_in)
		p->infile = ft_open_redir(last_in->key, last_in->mode, 0644);
	if (last_out)
		p->outfile = ft_open_redir(last_out->key, last_out->mode, 0644);
}

void	setup_redir(t_redir *redirection, t_pipex *p)
{
	t_redir	*redir;
	t_redir	*last_in;
	t_redir	*last_out;

	p->infile = 0;
	p->outfile = 0;
	redir = redirection;
	last_in = NULL;
	last_out = NULL;
	while (redir)
	{
		if (!test_redir_open(redir->key, redir->mode, 0644))
		{
			p->infile = -1;
			return ;
		}
		if (is_out_redir(redir->mode))
			last_out = redir;
		else
			last_in = redir;
		redir = redir->next;
	}
	save_redir_fds(last_in, last_out);
}
