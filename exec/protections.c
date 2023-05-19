/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:31:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/19 20:33:51 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *file, int mode, int perm)
{
	int	fd;

	if (mode == IN)
		fd = open(file, IN_FLAGS, perm);
	else if (mode == HEREDOC)
		fd = open(file, HEREDOC_FLAGS, perm);
	else if (mode == HEREDOC_EXP)
		fd = open(file, HEREDOC_FLAGS, perm);
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
	if (*fd < 0 || *fd > OPEN_MAX)
		return ;
	if (close(*fd) == -1)
	{
		g_sh->pipe_exit = 1;
		exit_only_child(1);
	}
	*fd = -2;
}

void	ft_dup2(int file1, int file2)
{
	int	success;

	success = dup2(file1, file2);
	if (success == -1)
	{
		g_sh->pipe_exit = 1;
		exit_only_child(1);
	}
}

void	ft_execve(char *const *argv, char *const *envp)
{
	int	success;

	success = execve(argv[0], argv, envp);
	if (success == -1)
	{
		g_sh->pipe_exit = 1;
		exit_only_child(1);
	}
}
