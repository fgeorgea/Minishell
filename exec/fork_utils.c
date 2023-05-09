/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:42:37 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/09 12:14:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_signal(int EXIT_MACRO)
{
	if (EXIT_MACRO != 0)
		ft_exit(EXIT_MACRO);
}

void	link_files(int fildes, int fildes2)
{
	ft_dup2(fildes, fildes2);
	ft_close(&fildes);
}
