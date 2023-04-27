/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/28 00:49:15 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork(int pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	p->pids[pos] = fork();
	if (p->pids[pos] == -1)
		ft_error(FORK_ERR, -1);
}

pid_t	*ft_createfork_array(t_pipex *p)
{
	pid_t	*array;

	array = malloc(sizeof(pid_t) * (p->nbr_fork));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	return (array);
}

void	ft_first_child(t_cmd *cmd, t_pipex *p)
{
	ft_close(&p->pipefd[0][0]);
	p->outfile = open_outfile(cmd);
	p->infile = open_infile(cmd);
	if (p->infile > 0)
		ft_dup2(p->infile, STDIN_FILENO);
	if (p->infile == -2)
		exit(0);
	ft_close(&p->infile);
	if (p->outfile > 0)
		ft_dup2(p->outfile, STDOUT_FILENO);
	else
		ft_dup2(p->pipefd[0][1], STDOUT_FILENO);
	ft_close(&p->pipefd[0][1]);
	ft_close(&p->outfile);
	check_cmd(cmd->cmd);
	execve(cmd->cmd[0], cmd->cmd, p->env_array);
}

void	ft_last_child(int pos, t_cmd *cmd, t_pipex *p)
{
	p->outfile = open_outfile(cmd);
	p->infile = open_infile(cmd);
	if (p->infile > 0)
		ft_dup2(p->infile, STDIN_FILENO);
	else if (p->infile == -2)
		exit(0);
	else
		ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO);
	ft_close(&p->infile);
	ft_close(&p->pipefd[pos - 1][0]);
	if (p->outfile > 0)
	{
		ft_dup2(p->outfile, STDOUT_FILENO);
		ft_close(&p->outfile);
	}
	check_cmd(cmd->cmd);
	execve(cmd->cmd[0], cmd->cmd, p->env_array);
}

void	ft_middle_child(int pos, t_cmd *cmd, t_pipex *p)
{
	p->outfile = open_outfile(cmd);
	p->infile = open_infile(cmd);
	if (p->infile > 0)
		ft_dup2(p->infile, STDIN_FILENO);
	else if (p->infile == -2)
		exit(0);
	else
		ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO);
	ft_close(&p->pipefd[pos - 1][0]);
	ft_close(&p->infile);
	if (p->outfile > 0)
		ft_dup2(p->outfile, STDOUT_FILENO);
	else
		ft_dup2(p->pipefd[pos][1], STDOUT_FILENO);
	ft_close(&p->pipefd[pos][1]);
	check_cmd(cmd->cmd);
	execve(cmd->cmd[0], cmd->cmd, p->env_array);
}
