/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:47:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/11 18:06:54 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (compare_keys(cmd, "cd") || compare_keys(cmd, "echo")
		|| compare_keys(cmd, "env") || compare_keys(cmd, "exit")
		|| compare_keys(cmd, "unset") || compare_keys(cmd, "pwd")
		|| compare_keys(cmd, "export"))
		return (1);
	return (0);
}

void	exec_builtin(char *cmd, char **arg)
{
	update_last_cmd(arg);
	if (compare_keys(cmd, "cd"))
		ft_cd(arg[1]);
	else if (compare_keys(cmd, "echo"))
		ft_echo(&arg[1]);
	else if (compare_keys(cmd, "env"))
		ft_env();
	else if (compare_keys(cmd, "exit"))
		ft_exit_builtin(&arg[1]);
	else if (compare_keys(cmd, "unset"))
		ft_unset(&arg[1]);
	else if (compare_keys(cmd, "pwd"))
		ft_pwd();
	else if (compare_keys(cmd, "export"))
		ft_export(&arg[1]);
}
