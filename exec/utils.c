/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:55:29 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 21:00:23 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Exits current program only if it is a child
void	exit_only_child(int exit_code)
{
	t_pipex	*p;

	p = g_sh->pipex;
	if (p->nbr_fork <= 0)
		return ;
	exit(exit_code);
}

// Sets the exit code by checking if we are on the last cmd.
void	set_exit(int exit_code)
{
	if (g_sh->is_exit_lst_cmd)
		g_sh->pipe_exit = exit_code;
}

void	set_lst_cmd(int pos)
{
	if (pos == (int)g_sh->pipex->nbr_cmds - 1)
		g_sh->is_exit_lst_cmd = 1;
}
