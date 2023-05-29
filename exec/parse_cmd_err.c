/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:55:44 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/29 17:46:49 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks wheter the cmd is a relative path or not.
int	is_relative_path(const char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	try_catch_cmd(char **cmd)
{
	if (is_relative_path(cmd[0]) && does_cmd_exist(cmd[0]))
		return ;
	if (!is_relative_path(cmd[0]))
		print_err(cmd[0], NULL, CNF, 127);
	else if (is_relative_path(cmd[0]) && access(cmd[0], F_OK))
		print_err(cmd[0], NULL, NSFOD, 127);
	else
		print_err(cmd[0], NULL, ": Permission denied", 126);
	exit_only_child(g_sh->pipe_exit);
}
