/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/14 20:24:16 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_last_cmd(const char **cmd)
{
	int	array_len;

	array_len = 0;
	if (!cmd || !*cmd)
		return ;
	array_len = arraylen(cmd);
	change_env_value("_", cmd[array_len - 1]);
	lst_to_array(&g_sh->env);
}

void	check_cmd(char **cmd)
{
	if (is_builtin(cmd[0]))
		exec_builtin(cmd[0], (const char **)cmd);
	found_cmd(cmd);
}

int	check_builtins_n_missing_path(t_pipex *p, t_cmd *cmd)
{
	if (is_builtin(cmd->cmd[0]) && p->nbr_pipe == 0)
	{
		exec_builtin(cmd->cmd[0], (const char **)cmd->cmd);
		return (1);
	}
	if (!(is_builtin(cmd->cmd[0])) && (p->nbr_paths == 0))
	{
		print_err(cmd->cmd[0], NULL, ": No such file or directory\n");
		return (1);
	}
	return (0);
}
