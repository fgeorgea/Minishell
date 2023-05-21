/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_stdout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:47:19 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/21 17:59:27 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Duplicates a file descriptor and returns the new one.
int	ft_dup(int fildes)
{
	int	dup_fildes;

	if (g_sh->pipex->nbr_fork > 0)
		return (-2);
	dup_fildes = dup(fildes);
	if (dup_fildes == -1)
		ft_exit(EXIT_DUP_FAILURE);
	return (dup_fildes);
}

// Restores STDOUT after single builtin redirection occured.
void	restore_stdout(int dup_stdout)
{
	if (g_sh->pipex->nbr_fork > 0)
		return ;
	if (close(STDOUT_FILENO) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	link_files(dup_stdout, STDOUT_FILENO);
}
