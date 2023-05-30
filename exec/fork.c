/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/30 17:30:34 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Protected versin of the fork function.
int	ft_fork(size_t pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	p->pids[pos] = fork();
	if (p->pids[pos] == -1)
	{
		close_all_pipes();
		print_perror("fork", ": ", 1);
		g_sh->pipe_exit = 1;
		return (0);
	}
	return (1);
}

pid_t	*create_fork_array(const t_pipex *p)
{
	pid_t	*array;

	if (g_sh->cmd->cmd && p->nbr_cmds == 1 && is_builtin(g_sh->cmd->cmd[0]))
		return (NULL);
	array = calloc(sizeof(pid_t), (p->nbr_fork));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	return (array);
}

void	first_child(const t_pipex *p)
{
	if (p->infile > 0)
		link_files(p->infile, STDIN_FILENO);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	else if (p->nbr_pipe > 0)
		link_files(p->pipefd[0][1], STDOUT_FILENO);
}

void	last_child(size_t pos, const t_pipex *p)
{
	if (p->infile > 0)
		link_files(p->infile, STDIN_FILENO);
	else
		link_files(p->pipefd[pos - 1][0], STDIN_FILENO);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
}

void	middle_child(size_t pos, const t_pipex *p)
{
	if (p->infile > 0)
		link_files(p->infile, STDIN_FILENO);
	else
		link_files(p->pipefd[pos - 1][0], STDIN_FILENO);
	if (p->outfile > 0)
		link_files(p->outfile, STDOUT_FILENO);
	else
		link_files(p->pipefd[pos][1], STDOUT_FILENO);
}
