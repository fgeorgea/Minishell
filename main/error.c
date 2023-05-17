/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:29:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/14 16:17:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(const char *cmd, const char *input, const char *message)
{
	ft_putstr_fd("Minishell: ", 2);
	if (cmd)
		ft_putstr_fd((char *)cmd, 2);
	if (input)
		ft_putstr_fd((char *)input, 2);
	if (message)
		ft_putstr_fd((char *)message, 2);
}

void	ft_exit(int status)
{
	if (status != EXIT_SUCCESS)
		perror(g_sh->name);
	ft_free_global();
	exit(status);
}
