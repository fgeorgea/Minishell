/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/10 16:12:02 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_cmd(char **cmd)
{
	int	nbr_arg;
	int	does_cmd_exist;
	int	is_cmd_builtin;

	nbr_arg = arraylen(cmd);
	does_cmd_exist = 0;
	is_cmd_builtin = is_builtin(cmd[0], cmd);
	if (!is_cmd_builtin)
		does_cmd_exist = found_cmd(cmd);
	change_env_value("_", cmd[nbr_arg - 1]);
	if (!does_cmd_exist || is_cmd_builtin)
		exit(EXIT_SUCCESS);
}
