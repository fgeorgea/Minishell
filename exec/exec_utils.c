/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 12:38:13 by fgeorgea         ###   ########.fr       */
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
	if (!cmd[0][0])
		return ;
	while (p->paths && p->paths[i] && errno != EISDIR)
	{
		if (try_cat_path_cmd_underscore(cmd, i))
			return ;
		i++;
	}
}

// Updates the '_' env value, which is the last argument of the last cmd.
void	update_last_cmd(const char **cmd)
{
	int	array_len;

	array_len = 0;
	if (!cmd)
		return ;
	if (g_sh->pipex->nbr_cmds > 1 || !*cmd)
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
	{
		exec_builtin(cmd[0], (const char **)cmd);
		exit(g_sh->pipe_exit);
	}
	if (g_sh->pipex->nbr_paths > 0)
		found_cmd(cmd);
	else if (!does_cmd_exist(cmd[0]))
	{
		print_perror(cmd[0], ": ", 127);
		exit(127);
	}
}

// If there is only 1 cmd and it is a builtin, -> exec outside of child.
int	is_single_builtin(void)
{
	t_pipex	*p;
	t_cmd	*cmd;

	p = g_sh->pipex;
	cmd = g_sh->cmd;
	if ((cmd->cmd && p->nbr_cmds == 1)
		&& (is_builtin(cmd->cmd[0]) || is_directory(cmd->cmd[0])))
	{
		g_sh->is_exit_lst_cmd = 1;
		if (is_directory(cmd->cmd[0]))
			cd_builtin(cmd->cmd[0]);
		else
			exec_builtin(cmd->cmd[0], (const char **)cmd->cmd);
		return (1);
	}
	return (0);
}

void	ft_execve(char *const *argv, char *const *envp)
{
	int	success;

	success = execve(argv[0], argv, envp);
	if (success == -1 && errno == EACCES)
	{
		print_perror(argv[0], ": ", 126);
		exit_only_child(126);
	}
	else if (success == -1)
		ft_exit(EXIT_EXECVE_FAILURE);
}
