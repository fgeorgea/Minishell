/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:19:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork(int pos, t_pipex *p)
{
	p->pids[pos] = fork();
	if (p->pids[pos] == -1)
		ft_error(p, FORK_ERR, -1);
}

pid_t	*ft_createfork_array(t_pipex *p)
{
	int		i;
	pid_t	*array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(pid_t) * (p->nbr_fork));
	if (!array)
		ft_error(p, "Failed to create the fork array\n", -1);
	return (array);
}

void	ft_first_child(char **env, t_pipex *p)
{
	ft_close(&p->pipefd[0][0], p);
	ft_close(&p->outfile, p);
	ft_dup2(p->infile, STDIN_FILENO, p);
	ft_close(&p->infile, p);
	ft_dup2(p->pipefd[0][1], STDOUT_FILENO, p);
	ft_close(&p->pipefd[0][1], p);
	execve(p->lst->content[0], p->lst->content, env);
}

void	ft_last_child(int pos, char **env, t_pipex *p)
{
	ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO, p);
	ft_close(&p->pipefd[pos - 1][0], p);
	ft_dup2(p->outfile, STDOUT_FILENO, p);
	ft_close(&p->outfile, p);
	execve(p->lst->content[0], p->lst->content, env);
}

void	ft_middle_child(int pos, char **env, t_pipex *p)
{
	ft_close(&p->outfile, p);
	ft_dup2(p->pipefd[pos - 1][0], STDIN_FILENO, p);
	ft_close(&p->pipefd[pos - 1][0], p);
	ft_dup2(p->pipefd[pos][1], STDOUT_FILENO, p);
	ft_close(&p->pipefd[pos][1], p);
	execve(p->lst->content[0], p->lst->content, env);
}
