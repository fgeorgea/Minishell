/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:29:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/25 16:24:49 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *cmd, char *input, char *message, int exit_code)
{
	ft_putstr_fd("Minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (input)
		ft_putstr_fd(input, 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (exit_code != -1)
		set_exit(exit_code);
}

void	print_perror(char *str1, char *str2, int exit_status)
{
	ft_putstr_fd("Minishell: ", 2);
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (exit_status != -1)
		set_exit(exit_status);
	perror(NULL);
}

void	ft_exit(int status)
{
	rl_clear_history();
	if (status != EXIT_SUCCESS)
		perror(g_sh->name);
	ft_free_global();
	exit(status);
}
