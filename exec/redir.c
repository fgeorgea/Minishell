/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/23 18:21:06 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_redir_open(char *file, int mode, int perm)
{
	int	fd;

	fd = ft_open_redir(file, mode, perm);
	if (fd == -1)
	{
		print_perror(file, ": ", 1);
		return (0);
	}
	ft_close(&fd);
	return (1);
}

/*
	Returns a reference to the last OUT redir.
	Returns NULL if there are no OUT redir.
*/
static t_redir	*get_out_redir(t_redir **redirection)
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
				return (NULL);
			last = redir;
		}
		redir = redir->next;
	}
	return (last);
}

/*
	Opens the outfile and returns the file descriptor.
	Returns -1 if there is no redir.
*/
int	open_outfile(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = get_out_redir(&cmd->redir);
	if (!redir && g_sh->pipe_exit == 0)
		return (0);
	if (!redir && g_sh->pipe_exit == 1)
		return (-1);
	fd = ft_open_redir(redir->key, redir->mode, 0644);
	if (fd == -1)
		print_err(redir->key, ": ", NULL, 1);
	return (fd);
}

/*
	Opens every heredoc if there are any.
	Returns the last IN redir.
	Returns NULL if there is no IN redir.
*/
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
			here_doc(redir->key);
		if (redir->mode == HEREDOC_EXP)
			ft_here_doc_exp(redir->key);
		if (redir->mode == IN)
		{
			if (!test_redir_open(redir->key, IN, 0644))
				return (NULL);
		}
		if (redir->mode != OUT && redir->mode != OUT_APP)
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
*/
int	open_infile(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = get_in_redir(&cmd->redir);
	if (!redir && g_sh->pipe_exit == 0)
		return (0);
	if (!redir && g_sh->pipe_exit == 1)
		return (-1);
	fd = ft_open_redir(redir->key, redir->mode, 0644);
	if (fd == -1)
		print_perror(redir->key, ": ", 1);
	return (fd);
}
