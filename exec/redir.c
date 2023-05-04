/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 01:44:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*get_out_redir(t_redir **redirection)
{
	int		tmp_fd;
	t_redir	*redir;
	t_redir	*last;

	if (!redirection || !*redirection)
		return (NULL);
	redir = *redirection;
	last = NULL;
	while (redir)
	{
		if (last && (redir->mode == OUT || redir->mode == OUT_APP))
		{
			if (last->mode == OUT)
				tmp_fd = ft_open(last->key, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else
				tmp_fd = ft_open(last->key, O_WRONLY | O_APPEND | O_CREAT, 0644);
			ft_close(&tmp_fd);
		}
		if ((redir->mode == OUT || redir->mode == OUT_APP))
			last = redir;
		redir = redir->next;
	}
	return (last);
}

int	open_outfile(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = get_out_redir(&cmd->redir);
	if (!redir)
		return (-1);
	if (redir->mode == OUT)
	{
		fd = ft_open(redir->key, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		return (fd);
	}
	fd = ft_open(redir->key, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

t_redir	*get_in_redir(t_redir **redirection)
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
			ft_here_doc(redir->key);
		//if (redir->mode == HEREDOC_EXP)
		//	ft_here_doc_exp(redir->key);
		if (redir->mode == HEREDOC || redir->mode == IN)
			last = redir;
		redir = redir->next;
	}
	return (last);
}

int	open_infile(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = get_in_redir(&cmd->redir);
	if (!redir || !redir->key)
		return (0);
	if (!file_exist(redir->key) && redir->mode != HEREDOC)
	{
		ft_putstr_fd(g_sh->name, 2);
		ft_putstr_fd(redir->key, 2);
		ft_putstr_fd(": file not found\n", 2);
		exit(1);
	}
	if (redir->mode == IN)
		fd = ft_open(redir->key, O_RDONLY, -1);
	else
		fd = ft_open(TMP_FILE, O_RDONLY, -1);
	return (fd);
}
