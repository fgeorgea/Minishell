/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:31:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/01 23:51:27 by fgeorgea         ###   ########.fr       */
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
	if (!fd)
	{
		g_sh->pipex->exit_macro = EXIT_OPEN_FAILURE;
		ft_exit(EXIT_OPEN_FAILURE);
	}
	return (fd);
}

void	ft_close(int *fd)
{
	if (*fd == -2)
		return ;
	if (close(*fd) == -2)
	{
		g_sh->pipex->exit_macro = EXIT_CLOSE_FAILURE;
		ft_exit(EXIT_CLOSE_FAILURE);
	}
	*fd = -2;
}

void	ft_dup2(int file1, int file2)
{
	int	success;

	success = dup2(file1, file2);
	if (!success)
	{
		g_sh->pipex->exit_macro = EXIT_DUP2_FAILURE;
		ft_exit(EXIT_DUP2_FAILURE);
	}
}

void	ft_waitpid(void)
{
	int		i;
	int		success;
	int		status;
	t_pipex	*p;

	i = 0;
	p = g_sh->pipex;
	while (i < p->nbr_fork)
	{
		success = waitpid(p->pids[i], &status, 0);
		if (!success)
			ft_exit(EXIT_WAITPID_FAILURE);
		i++;
	}
}

void	ft_execve(const char *path, char *const argv[], char *const envp[])
{
	int	success;

	check_cmd((char **)argv);
	success = execve(path, argv, envp);
	if (!success)
		ft_exit(EXIT_EXECVE_FAILURE);
}
