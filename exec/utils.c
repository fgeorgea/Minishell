/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:55:29 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:21:02 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tablen(char **tab, t_pipex *p)
{
	int	i;

	i = 0;
	if (!tab)
		ft_error(p, "Failed to get the size of the array\n", -1);
	while (tab[i])
		i++;
	return (i);
}

void	ft_close(int *fd, t_pipex *p)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		ft_error(p, CLOSE_ERR, -1);
	*fd = -1;
}

void	ft_dup2(int file1, int file2, t_pipex *p)
{
	int	success;

	success = dup2(file1, file2);
	if (success == -1)
		ft_error(p, DUP2_ERR, -1);
}

void	ft_waitpid(t_pipex *p)
{
	int	i;
	int	success;
	int	status;

	i = 0;
	while (i < p->nbr_fork)
	{
		success = waitpid(p->pids[i], &status, 0);
		if (success == -1)
			ft_error(p, WAITPID_ERR, -1);
		i++;
	}
}
