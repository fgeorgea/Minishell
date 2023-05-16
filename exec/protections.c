/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:31:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/16 16:56:37 by fgeorgea         ###   ########.fr       */
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
		ft_exit(EXIT_OPEN_FAILURE);
	return (fd);
}

void	ft_close(int *fd)
{
	if (*fd < 0 || *fd > OPEN_MAX)
		return ;
	if (close(*fd) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	*fd = -2;
}

void	ft_dup2(int file1, int file2)
{
	int	success;

	success = dup2(file1, file2);
	if (success == -1)
		ft_exit(EXIT_DUP2_FAILURE);
}

void	ft_waitpid(void)
{
	size_t	i;
	int		success;
	int		status;
	t_pipex	*p;

	i = 0;
	p = g_sh->pipex;
	p->is_in_child = 1;
	if ((p->nbr_cmds == 1 && is_builtin(g_sh->cmd->cmd[0]))
		|| (p->nbr_paths < 1))
		return ;
	while ((i < p->nbr_fork) && p->pids[i] && p->pids[i] != -1)
	{
		success = waitpid(p->pids[i], &status, 0);
		if (success == -1)
			ft_exit(EXIT_WAITPID_FAILURE);
		i++;
	}
	p->is_in_child = 0;
	if (g_sh->pipe_exit != 0)
		return ;
	g_sh->pipe_exit = status;
	g_sh->pipe_exit /= 256;
}

void	ft_execve(char *const *argv, char *const *envp)
{
	int	success;

	success = execve(argv[0], argv, envp);
	if (success == -1)
		ft_exit(EXIT_EXECVE_FAILURE);
}
