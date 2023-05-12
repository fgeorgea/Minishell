/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:47:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/12 01:41:39 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(const char *cmd)
{
	if (compare_keys(cmd, "cd") || compare_keys(cmd, "echo")
		|| compare_keys(cmd, "env") || compare_keys(cmd, "exit")
		|| compare_keys(cmd, "unset") || compare_keys(cmd, "pwd")
		|| compare_keys(cmd, "export"))
		return (1);
	return (0);
}

void	exec_builtin(const char *cmd, const char **arg)
{
	update_last_cmd(arg);
	if (compare_keys(cmd, "cd"))
		cd_builtin(arg[1]);
	else if (compare_keys(cmd, "echo"))
		echo_builtin(&arg[1]);
	else if (compare_keys(cmd, "env"))
		env_builtin();
	else if (compare_keys(cmd, "exit"))
		exit_builtin(&arg[1]);
	else if (compare_keys(cmd, "unset"))
		unset_builtin(&arg[1]);
	else if (compare_keys(cmd, "pwd"))
		pwd_builtin();
	else if (compare_keys(cmd, "export"))
		export_builtin(&arg[1]);
}