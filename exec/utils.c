/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:55:29 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/27 20:03:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		ft_error("Failed to get the size of the array\n", -1);
	while (tab[i])
		i++;
	return (i);
}

void	ft_close(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		ft_error(CLOSE_ERR, -1);
	*fd = -1;
}

void	ft_dup2(int file1, int file2)
{
	int	success;

	success = dup2(file1, file2);
	if (success == -1)
		ft_error(DUP2_ERR, -1);
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
		if (success == -1)
			ft_error(WAITPID_ERR, -1);
		i++;
	}
}

int	ft_open(char *file, int flags, int perm)
{
	int	fd;

	if (perm == -1)
		fd = open(file, flags);
	else
		fd = open(file, flags, perm);
	if (fd == -1)
		ft_error("Open failed\n", -1);
	return (fd);
}
