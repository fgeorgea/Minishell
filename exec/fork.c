/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/27 14:36:34 by fgeorgea         ###   ########.fr       */
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
	int		i;
	pid_t	*array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(pid_t) * (p->nbr_fork));
	if (!array)
		ft_error("Failed to create the fork array\n", -1);
	return (array);
}

void	ft_first_child(t_cmd *cmd, t_pipex *p)
{
	ft_close(&p->pipefd[0][0]);
	//ft_close(&p->outfile);
	//ft_dup2(p->infile, STDIN_FILENO);
	//ft_close(&p->infile);
	ft_dup2(p->pipefd[0][1], STDOUT_FILENO);
	ft_close(&p->pipefd[0][1]);
	if (!check_cmd(cmd->cmd))
		exit(0);
	execve(cmd->cmd[0], cmd->cmd, p->env_array);
}

void	ft_last_child(int pos, t_cmd *cmd, t_pipex *p)
{
	ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO);
	ft_close(&p->pipefd[pos - 1][0]);
	//ft_dup2(p->outfile, STDOUT_FILENO);
	//ft_close(&p->outfile);
	if (!check_cmd(cmd->cmd))
		exit(0);
	execve(cmd->cmd[0], cmd->cmd, p->env_array);
}

void	ft_middle_child(int pos, t_cmd *cmd, t_pipex *p)
{
	//ft_close(&p->outfile);
	ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO);
	ft_close(&p->pipefd[pos - 1][0]);
	ft_dup2(p->pipefd[pos][1], STDOUT_FILENO);
	ft_close(&p->pipefd[pos][1]);
	if (!check_cmd(cmd->cmd))
		exit(0);
	execve(cmd->cmd[0], cmd->cmd, p->env_array);
}
