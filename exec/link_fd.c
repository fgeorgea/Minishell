/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/26 17:25:43 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	link_files(int fildes, int fildes2)
{
	ft_dup2(fildes, fildes2);
	ft_close(&fildes);
}

void	ft_dup2(int file1, int file2)
{
	int	success;

	success = dup2(file1, file2);
	if (success == -1)
	{
		set_exit(1);
		exit_only_child(1);
	}
}
