/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/19 20:35:47 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	test_open(char *file, int flags, int perm)
{
	int	fd;

	fd = ft_open(file, flags, perm);
	if (fd == -1)
	{
		print_err(file, ": ", NULL, 1);
		perror(NULL);
		exit_only_child(1);
	}
	else
		ft_close(&fd);
}

/*
	Create all out redirections and returns the last OUT redir node.
	Returns NULL if there is no OUT redir.
*/
static t_redir	*get_out_redir(t_redir **redirection)
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
			tmp_fd = ft_open(last->key, redir->mode, 0644);
			ft_close(&tmp_fd);
		}
		if ((redir->mode == OUT || redir->mode == OUT_APP))
			last = redir;
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
	if (!redir)
		return (0);
	fd = ft_open(redir->key, redir->mode, 0644);
	if (fd == -1)
	{
		perror(NULL);
		exit_only_child(1);
	}
	return (fd);
}

/*
	Opens every heredoc if there are any.
	Returns the last IN redir.
	Returns NULL if there is no IN redir.
	'!' ->exits if there is a non existing infile input.
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
			test_open(redir->key, IN, -1);
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
int	open_infile(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	redir = get_in_redir(&cmd->redir);
	if (!redir || !redir->key)
		return (0);
	fd = ft_open(redir->key, redir->mode, 0644);
	if (fd == -1)
	{
		print_err(redir->key, ": ", NULL, 1);
		perror(NULL);
		exit_only_child(1);
	}
	return (fd);
}
