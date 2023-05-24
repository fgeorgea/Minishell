/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:55:44 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/24 18:18:38 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	try_catch_cmd(char **cmd)
{
	if (is_relative_path(cmd[0]) && does_cmd_exist(cmd[0]))
		return (1);
	if (errno == EISDIR)
		return (0);
	if (!is_relative_path(cmd[0]))
		print_err(cmd[0], NULL, CNF, 127);
	else
		print_err(cmd[0], NULL, NSFOD, 127);
	exit(g_sh->pipe_exit);
}