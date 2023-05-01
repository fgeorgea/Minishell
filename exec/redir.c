/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/01 18:25:26 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*get_out_redir(t_redir **redirection)
{
	int		tmp_fd;
	t_redir	*redir;

	if (!redirection)
		return (NULL);
	redir = *redirection;
	while (redir && (redir->mode != OUT || redir->mode != OUT_APP))
		redir = redir->next;
	if (!redir || redir->mode != OUT || redir->mode != OUT_APP)
		return (NULL);
	while (redir->next)
	{
		tmp_fd = ft_open(redir->key, O_WRONLY | O_CREAT, 0644);
		ft_close(&tmp_fd);
		redir = redir->next;
	}
	return (redir);
}

int	open_outfile(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = get_out_redir(&cmd->redir);
	if (!redir && !redir->key)
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

	if (!redirection)
		return (NULL);
	redir = *redirection;
	while (redir->next && (redir->next->mode == IN || redir->next->mode == HEREDOC))
	{
		if (redir->mode == IN && !file_exist(redir->key))
			exit(1);
		if (redir->mode == HEREDOC)
			ft_here_doc(redir->key);
		redir = redir->next;
	}
	if (!redir || (redir->mode != IN && redir->mode != HEREDOC))
		return (NULL);
	if (redir->mode == HEREDOC)
		ft_here_doc(redir->key);
	return (redir);
}

int	open_infile(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = get_in_redir(&cmd->redir);
	if (!redir && !redir->key)
		return (0);
	if (!file_exist(redir->key))
	{
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
