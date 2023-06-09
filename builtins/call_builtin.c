/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:47:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/07/01 04:55:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strcmp_strict(cmd, "cd") || ft_strcmp_strict(cmd, "echo")
		|| ft_strcmp_strict(cmd, "env") || ft_strcmp_strict(cmd, "exit")
		|| ft_strcmp_strict(cmd, "unset") || ft_strcmp_strict(cmd, "pwd")
		|| ft_strcmp_strict(cmd, "export") || ft_strcmp_strict(cmd, "alias")
		|| ft_strcmp_strict(cmd, "unalias"))
		return (1);
	return (0);
}

static void	exec_builtin2(const char *cmd, const char **arg)
{
	if (ft_strcmp_strict(cmd, "export"))
		export_builtin(&arg[1]);
	else if (ft_strcmp_strict(cmd, "alias"))
		alias_builtin(&arg[1]);
	else if (ft_strcmp_strict(cmd, "unalias"))
		unalias_builtin(&arg[1]);
}

void	exec_builtin(const char *cmd, const char **arg)
{
	update_last_cmd(arg);
	g_sh->pipex->dup_stdout = ft_dup(STDOUT_FILENO);
	if (!builtin_redirection())
	{
		set_exit(1);
		restore_stdout(g_sh->pipex->dup_stdout);
		return ;
	}
	if (ft_strcmp_strict(cmd, "cd"))
		cd_builtin(arg[1]);
	else if (ft_strcmp_strict(cmd, "echo"))
		echo_builtin(&arg[1]);
	else if (ft_strcmp_strict(cmd, "env"))
		env_builtin(&arg[1]);
	else if (ft_strcmp_strict(cmd, "exit"))
		exit_builtin(&arg[1]);
	else if (ft_strcmp_strict(cmd, "unset"))
		unset_builtin(&arg[1]);
	else if (ft_strcmp_strict(cmd, "pwd"))
		pwd_builtin();
	exec_builtin2(cmd, arg);
	restore_stdout(g_sh->pipex->dup_stdout);
}
