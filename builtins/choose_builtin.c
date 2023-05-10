/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:47:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/11 01:47:00 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd, char **arg)
{
	int	is_builtin;

	is_builtin = 1;
	if (compare_keys(cmd, "cd"))
		ft_cd(arg[1]);
	else if (compare_keys(cmd, "echo"))
		ft_echo(&arg[1]);
	else if (compare_keys(cmd, "env"))
		ft_env();
	else if (compare_keys(cmd, "exit"))
		ft_exit_builtin();
	else if (compare_keys(cmd, "unset"))
		ft_unset(&arg[1]);
	else if (compare_keys(cmd, "pwd"))
		ft_pwd();
	else if (compare_keys(cmd, "export"))
		ft_export(&arg[1]);
	else
		is_builtin = 0;
	return (is_builtin);
}
