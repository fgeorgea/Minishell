/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:29:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/19 14:05:39 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *cmd, char *input, char *message, int exit_status)
{
	ft_putstr_fd("Minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (input)
		ft_putstr_fd(input, 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (exit_status != -1)
		g_sh->pipe_exit = exit_status;
}

void	ft_exit(int status)
{
	if (status != EXIT_SUCCESS)
		perror(g_sh->name);
	ft_free_global();
	exit(status);
}
