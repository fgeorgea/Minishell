/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:58:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 15:26:02 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork(int pos, t_global *g)
{
	g->pids[pos] = fork();
	if (g->pids[pos] == -1)
		ft_error(g, FORK_ERR);
}

pid_t	*ft_createfork_array(t_global *g)
{
	int		i;
	pid_t	*array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(pid_t) * (g->nbr_fork));
	if (!array)
		ft_error(g, "Failed to create the fork array\n");
	return (array);
}

void	ft_first_child(char **env, t_global *g)
{
	ft_close(&g->pipefd[0][0], g);
	ft_close(&g->outfile, g);
	ft_dup2(g->infile, STDIN_FILENO, g);
	ft_close(&g->infile, g);
	ft_dup2(g->pipefd[0][1], STDOUT_FILENO, g);
	ft_close(&g->pipefd[0][1], g);
	execve(g->lst->content[0], g->lst->content, env);
}

void	ft_last_child(int pos, char **env, t_global *g)
{
	ft_dup2(g->pipefd[pos - 1][0], STDIN_FILENO, g);
	ft_close(&g->pipefd[pos - 1][0], g);
	ft_dup2(g->outfile, STDOUT_FILENO, g);
	ft_close(&g->outfile, g);
	execve(g->lst->content[0], g->lst->content, env);
}

void	ft_middle_child(int pos, char **env, t_global *g)
{
	ft_close(&g->outfile, g);
	ft_dup2(g->pipefd[pos - 1][0], STDIN_FILENO, g);
	ft_close(&g->pipefd[pos - 1][0], g);
	ft_dup2(g->pipefd[pos][1], STDOUT_FILENO, g);
	ft_close(&g->pipefd[pos][1], g);
	execve(g->lst->content[0], g->lst->content, env);
}
