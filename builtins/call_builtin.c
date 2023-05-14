/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:47:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/14 03:04:51 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(const char *cmd)
{
	if (compare_keys(cmd, "cd") || compare_keys(cmd, "echo")
		|| compare_keys(cmd, "env") || compare_keys(cmd, "exit")
		|| compare_keys(cmd, "unset") || compare_keys(cmd, "pwd")
		|| compare_keys(cmd, "export"))
		return (1);
	return (0);
}

static void	builtin_redirection(void)
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

static int	ft_dup(int fildes)
{
	int	dup_stdout;

	if (g_sh->pipex->nbr_cmds > 1)
		return (-2);
	dup_stdout = dup(fildes);
	if (dup_stdout == -1)
		ft_exit(EXIT_DUP_FAILURE);
	return (dup_stdout);
}

static void	restore_stdout(int dup_stdout)
{
	if (g_sh->pipex->nbr_cmds > 1)
		return ;
	if (close(STDOUT_FILENO) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	link_files(dup_stdout, STDOUT_FILENO);
}

void	exec_builtin(const char *cmd, const char **arg)
{
	int	dup_stdout;

	dup_stdout = ft_dup(STDOUT_FILENO);
	update_last_cmd(arg);
	builtin_redirection();
	if (compare_keys(cmd, "cd"))
		cd_builtin(arg[1]);
	else if (compare_keys(cmd, "echo"))
		echo_builtin(&arg[1]);
	else if (compare_keys(cmd, "env"))
		env_builtin();
	else if (compare_keys(cmd, "exit"))
		exit_builtin(&arg[1]);
	else if (compare_keys(cmd, "unset"))
		unset_builtin(&arg[1]);
	else if (compare_keys(cmd, "pwd"))
		pwd_builtin();
	else if (compare_keys(cmd, "export"))
		export_builtin(&arg[1]);
	restore_stdout(dup_stdout);
}
