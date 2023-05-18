/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/19 01:42:30 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (last->mode == OUT)
				tmp_fd = ft_open(last->key, OUT_FLAGS, 0644);
			else
				tmp_fd = ft_open(last->key, OUT_APP_FLAGS, 0644);
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
		return (-1);
	if (redir->mode == OUT)
		fd = ft_open(redir->key, OUT_FLAGS, 0644);
	else
		fd = ft_open(redir->key, OUT_APP_FLAGS, 0644);
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
		if (redir->mode == IN && !file_exist(redir->key))
		{
			print_err(NULL, redir->key, ": file not found\n");
			exit(1);
		}
		if (redir->mode == HEREDOC || redir->mode == IN || redir->mode == HEREDOC_EXP)
			last = redir;
		redir = redir->next;
		if (g_sh->here_doc_status)
			return (0);
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
	if (!file_exist(redir->key) && redir->mode == IN)
	{
		print_err(NULL, redir->key, ": file not found\n");
		exit(1);
	}
	if (redir->mode == IN)
		fd = ft_open(redir->key, IN_FLAGS, -1);
	else
		fd = ft_open(TMP_FILE, IN_FLAGS, 0644);
	return (fd);
}
