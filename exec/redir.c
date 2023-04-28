/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/28 15:33:26 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*get_out_redir(t_redir **redirection)
{
	t_redir	*redir;

	if (!redirection)
		return (NULL);
	redir = *redirection;
	while (redir)
		redir = redir->next;
	if (redir->mode == OUT || redir->mode == OUT_APP)
		return (redir);
	return (NULL);
}

t_redir	*get_in_redir(t_redir **redirection)
{
	t_redir	*redir;
	
	if (!redirection)
		return (NULL);
	redir = *redirection;
	while (redir && (redir->next->mode == IN || redir->next->mode == HEREDOC))
		redir = redir->next;
	if (redir && (redir->mode == IN || redir->mode == HEREDOC))
		return (redir);
	return (NULL);
}

int	open_infile(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = get_in_redir(&cmd->redir);
	if (!redir && !redir->key)
		return (-1);
	if (!access(redir->key, F_OK))
	{
		ft_putstr_fd(redir->key, 2);
		ft_putstr_fd("file not found\n", 2);
		return (-2);
	}
	if (redir->mode == IN)
	{	
		fd = ft_open(redir->key, O_RDONLY, -1);
		return (fd);
	}
	fd = ft_open(TMP_FILE, O_RDONLY, -1);
		return (fd);
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





