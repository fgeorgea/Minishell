/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:29:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/27 17:30:09 by fgeorgea         ###   ########.fr       */
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

static void	print_exit_err(int status)
{
	if (status == EXIT_SUCCESS)
		return ;
	else if (status == EXIT_MALLOC_FAILURE)
		print_err("MALLOC crash !", NULL, NULL, status);
	else if (status == EXIT_SIGNAL_FAILURE)
		print_err("SIGNAL crash !", NULL, NULL, status);
	else if (status == EXIT_OPEN_FAILURE)
		print_err("OPEN crash !", NULL, NULL, status);
	else if (status == EXIT_CLOSE_FAILURE)
		print_err("CLOSE crash !", NULL, NULL, status);
	else if (status == EXIT_PIPE_FAILURE)
		print_err("PIPE crash !", NULL, NULL, status);
	else if (status == EXIT_DUP2_FAILURE)
		print_err("DUP2 crash !", NULL, NULL, status);
	else if (status == EXIT_WAITPID_FAILURE)
		print_err("WAITPID crash !", NULL, NULL, status);
	else if (status == EXIT_EXECVE_FAILURE)
		print_err("EXECVE crash !", NULL, NULL, status);
	else if (status == EXIT_PWD_FAILURE)
		print_err("PWD crash !", NULL, NULL, status);
	else if (status == EXIT_DUP_FAILURE)
		print_err("DUP crash !", NULL, NULL, status);
	else
		print_perror(NULL, NULL, status);
}

void	ft_exit(int status)
{
	rl_clear_history();
	if (status != EXIT_SUCCESS)
		print_exit_err(status);
	ft_free_global();
	exit(status);
}
