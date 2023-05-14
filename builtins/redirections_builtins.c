/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:06:31 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/14 16:07:02 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_redirection(void)
{
	t_pipex	*p;
	t_cmd	*cmd;

	p = g_sh->pipex;
	if (p->nbr_cmds > 1)
		return ;
	cmd = g_sh->cmd;
	p->outfile = open_outfile(cmd);
	p->infile = open_infile(cmd);
	if (p->infile > 0)
		ft_close(&p->infile);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
}

int	ft_dup(int fildes)
{
	int	dup_stdout;

	if (g_sh->pipex->nbr_cmds > 1)
		return (-2);
	dup_stdout = dup(fildes);
	if (dup_stdout == -1)
		ft_exit(EXIT_DUP_FAILURE);
	return (dup_stdout);
}

void	restore_stdout(int dup_stdout)
{
	if (g_sh->pipex->nbr_cmds > 1)
		return ;
	if (close(STDOUT_FILENO) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	link_files(dup_stdout, STDOUT_FILENO);
}