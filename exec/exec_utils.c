/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/11 21:38:22 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_last_cmd(char **cmd)
{
	int	array_len;

	array_len = 0;
	if (!cmd || !*cmd)
		return ;
	array_len = arraylen((const char **)cmd);
	change_env_value("_", cmd[array_len - 1]);
	lst_to_array(&g_sh->env);
}

void	check_cmd(char **cmd)
{
	int	does_cmd_exist;
	int	is_cmd_builtin;

	does_cmd_exist = 0;
	is_cmd_builtin = is_builtin(cmd[0]);
	if (!is_cmd_builtin)
		does_cmd_exist = found_cmd(cmd);
	if (is_cmd_builtin)
		exec_builtin(cmd[0], cmd);
	if (!does_cmd_exist || is_cmd_builtin)
		exit(EXIT_SUCCESS);
}
