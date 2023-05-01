/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/01 17:02:08 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork(int pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	p->pids[pos] = fork();
	if (p->pids[pos] == -1)
		ft_exit(EXIT_FORK_FAILURE);
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
	{
		ft_dup2(p->infile, STDIN_FILENO);
		ft_close(&p->infile);
	}
	if (p->outfile > 0)
	{
		ft_dup2(p->outfile, STDOUT_FILENO);
		ft_close(&p->outfile);
	}
	else
		ft_dup2(p->pipefd[0][1], STDOUT_FILENO);
	ft_close(&p->pipefd[0][1]);
	check_cmd(cmd->cmd);
	ft_execve(cmd->cmd[0], cmd->cmd, p->env_array);
}

void	ft_last_child(int pos, t_cmd *cmd, t_pipex *p)
{
	p->outfile = open_outfile(cmd);
	p->infile = open_infile(cmd);
	if (p->infile > 0)
	{
		ft_dup2(p->infile, STDIN_FILENO);
		ft_close(&p->infile);
	}
	else
	{
		ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO);
		ft_close(&p->pipefd[pos - 1][0]);
	}
	if (p->outfile > 0)
	{
		ft_dup2(p->outfile, STDOUT_FILENO);
		ft_close(&p->outfile);
	}
	check_cmd(cmd->cmd);
	ft_execve(cmd->cmd[0], cmd->cmd, p->env_array);
}

void	ft_middle_child(int pos, t_cmd *cmd, t_pipex *p)
{
	p->outfile = open_outfile(cmd);
	p->infile = open_infile(cmd);
	if (p->infile > 0)
	{
		ft_dup2(p->infile, STDIN_FILENO);
		ft_close(&p->infile);
	}
	else
	{
		ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO);
		ft_close(&p->pipefd[pos - 1][0]);
	}
	if (p->outfile > 0)
	{
		ft_dup2(p->outfile, STDOUT_FILENO);
		ft_close(&p->outfile);
	}
	else
	{
		ft_dup2(p->pipefd[pos][1], STDOUT_FILENO);
		ft_close(&p->pipefd[pos][1]);	
	}
	check_cmd(cmd->cmd);
	ft_execve(cmd->cmd[0], cmd->cmd, p->env_array);
}
