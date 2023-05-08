/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:54:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/08 19:04:28 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_cmd(char **cmd)
{
	int	is_cmd_builtin;
	int	does_cmd_exist;
	int	nbr_arg;

	nbr_arg = ft_arraylen(cmd);
	is_cmd_builtin = is_builtin(cmd[0], cmd);
	if (is_cmd_builtin)
	{
		change_env_value("-", cmd[nbr_arg - 1]);
		exit(EXIT_SUCCESS);
	}
	does_cmd_exist = found_cmd(cmd);
	change_env_value("-", cmd[nbr_arg - 1]);
	if (!does_cmd_exist)
		exit(EXIT_SUCCESS);
}
