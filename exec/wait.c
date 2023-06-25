/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:45:41 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 21:08:09 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Will set the exit code properly by using the status of waitpid.
static void	save_exit_code(int status)
{
	if (status == SIGINT)
		status = 130 * 256;
	else if (status == SIGQUIT)
	{
		(void)write(2, "Quit: 3\n", 8);
		status = 131 * 256;
	}
	else if (g_sh->here_doc_status)
		status = 256;
	g_sh->pipe_exit = status / 256;
}

/*
	Waits for the child proccesses to finish.
	Will not proceed if:
	- There is more than 1 cmd and it is a builtin.
	- There are no PATHS.
*/
void	ft_waitpid(void)
{
	size_t	i;
	int		success;
	int		status;
	t_pipex	*p;

	i = 0;
	p = g_sh->pipex;
	status = 0;
	if (p->nbr_fork == 0)
		return ;
	p->is_in_child = 1;
	while (i < p->nbr_fork && p->pids[i] && p->pids[i] != -1)
	{
		success = waitpid(p->pids[i], &status, 0);
		if (success == -1)
			ft_exit(EXIT_WAITPID_FAILURE);
		i++;
	}
	p->is_in_child = 0;
	if (i < p->nbr_fork && p->pids[i] == -1)
		g_sh->pipe_exit = 1;
	else
		save_exit_code(status);
}
