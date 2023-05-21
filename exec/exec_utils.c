/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/21 20:49:41 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Will find the right path for the external cmd to replace the '_' env value.
static void	cat_cmd_for_underscore(char **cmd)
{
	size_t	i;
	t_pipex	*p;

	i = 0;
	p = g_sh->pipex;
	while (p->paths[i])
	{
		if (try_cat_path_cmd(cmd, i))
			return ;
		if ((i == p->nbr_paths - 1)
			&& (is_relative_path(cmd[0]) && does_cmd_exist(cmd[0])))
			return ;
		i++;
	}
	return ;
}

/*
	Updates the '_' env value. Which is the last argument of the last cmd.
	If the cmd does not have any arg, the value will be the path of the cmd.
	'!' -> It is set to empty if there are pipes/multiple cmds.
*/
void	update_last_cmd(const char **cmd)
{
	int	array_len;

	array_len = 0;
	if (!cmd || !*cmd)
		return ;
	if (g_sh->pipex->nbr_cmds > 1)
	{
		change_env_value("_", "");
		return ;
	}
	if (!is_builtin(cmd[0]) && arraylen(cmd) == 1)
		cat_cmd_for_underscore((char **)cmd);
	array_len = arraylen(cmd);
	change_env_value("_", cmd[array_len - 1]);
	lst_to_array(&g_sh->env);
}

/*
	Checks if a cmd is a builtin or an external cmd.
	If it is a builtin, it will execute manually.
	Otherwise, it will find the right path for the external cmd.
*/
void	check_cmd(char **cmd)
{
	if (is_builtin(cmd[0]))
		exec_builtin(cmd[0], (const char **)cmd);
	found_cmd(cmd);
}

/*
	Checks cmd is builtin and executes it outside of child -
	only if there is one cmd.
	Checks if there are PATHS, will print an error if an -
	external cmd is called with no PATH to find it.
*/
int	check_builtins(t_pipex *p, t_cmd *cmd)
{
	if (is_builtin(cmd->cmd[0]) && p->nbr_cmds == 1)
	{
		exec_builtin(cmd->cmd[0], (const char **)cmd->cmd);
		return (1);
	}
	return (0);
}

void	ft_execve(char *const *argv, char *const *envp)
{
	int	success;

	success = execve(argv[0], argv, envp);
	if (success == -1)
	{
		g_sh->pipe_exit = 1;
		exit_only_child(1);
	}
}
