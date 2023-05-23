/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:06:31 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/23 23:44:40 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Set up redirection for single builtin cmd.
int	builtin_redirection(void)
{
	t_pipex	*p;
	t_cmd	*cmd;

	p = g_sh->pipex;
	if (p->nbr_fork > 0)
		return (1);
	cmd = g_sh->cmd;
	p->infile = open_infile(cmd);
	if (p->infile == -1)
		return (0);
	ft_close(&p->infile);
	p->outfile = open_outfile(cmd);
	if (p->outfile == -1)
		return (0);
	else if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	return (1);
}
