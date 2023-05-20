/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:31:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/20 01:55:28 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *file, int flags, int perm)
{
	int	fd;

	if (perm == -1)
		fd = open(file, flags);
	else
		fd = open(file, flags, perm);
	if (fd == -1)
		g_sh->pipe_exit = -1;
	return (fd);
}

int	ft_open_redir(char *file, int mode, int perm)
{
	int	fd;

	if (mode == IN)
		fd = open(file, IN_FLAGS, perm);
	else if (mode == HEREDOC)
		fd = open(TMP_FILE, IN, perm);
	else if (mode == HEREDOC_EXP)
		fd = open(TMP_FILE, IN, perm);
	else if (mode == OUT)
		fd = open(file, OUT_FLAGS, perm);
	else if (mode == OUT_APP)
		fd = open(file, OUT_APP_FLAGS, perm);
	else
		fd = open(file, mode, perm);
	if (fd == -1)
		g_sh->pipe_exit = 1;
	return (fd);
}

void	ft_close(int *fd)
{
	if (*fd < 3 || *fd > OPEN_MAX)
		return ;
	if (close(*fd) == -1)
	{
		g_sh->pipe_exit = 1;
		exit_only_child(1);
	}
	*fd = -2;
}
