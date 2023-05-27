/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 17:44:32 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Will link 2 file descriptors and close the useless one.
void	link_files(int fildes, int fildes2)
{
	ft_dup2(fildes, fildes2);
	ft_close(&fildes);
}

// Protected version of dup2 function.
void	ft_dup2(int file1, int file2)
{
	int	success;

	success = dup2(file1, file2);
	if (success == -1 && (errno == EMFILE || errno == EBADF))
		ft_exit(EXIT_DUP2_FAILURE);
	else if (success == -1)
	{
		set_exit(1);
		exit_only_child(1);
	}
}
