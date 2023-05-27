/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:31:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 18:42:09 by fgeorgea         ###   ########.fr       */
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
	if (fd == -1 && (errno == EMFILE || errno == ENFILE))
		ft_exit(EXIT_OPEN_FAILURE);
	else if (fd == -1)
		set_exit(1);
	return (fd);
}

int	ft_open_redir(char *file, int mode, int perm)
{
	int	fd;

	if (mode == IN)
		fd = ft_open(file, O_RDONLY, perm);
	else if (mode == HEREDOC)
		fd = ft_open(g_sh->pipex->hd_tmp, O_RDONLY, perm);
	else if (mode == HEREDOC_EXP)
		fd = ft_open(g_sh->pipex->hd_tmp, O_RDONLY, perm);
	else if (mode == OUT)
		fd = ft_open(file, O_WRONLY | O_TRUNC | O_CREAT, perm);
	else if (mode == OUT_APP)
		fd = ft_open(file, O_WRONLY | O_APPEND | O_CREAT, perm);
	else
		fd = ft_open(file, mode, perm);
	return (fd);
}

// Protected version of close function. 
void	ft_close(int *fd)
{
	if (*fd < 3 || *fd > OPEN_MAX)
		return ;
	if (close(*fd) == -1)
	{
		set_exit(1);
		exit_only_child(1);
	}
	*fd = -2;
}
