/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:55:29 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/28 01:16:18 by fgeorgea         ###   ########.fr       */
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
		ft_exit(EXIT_CLOSE_FAILURE);
	*fd = -1;
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
			ft_exit(EXIT_WAITPID_FAILURE);
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
		ft_exit(EXIT_OPEN_FAILURE);
	return (fd);
}
