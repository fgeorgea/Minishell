/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/25 14:30:09 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child(int pos, char **env)
{
	t_pipex	*p;

	p = g_sh->pipex;
	if (pos == 0)
		ft_first_child(env, p);
	else if (pos == p->nbr_fork - 1)
		ft_last_child(pos, env, p);
	else
		ft_middle_child(pos, env, p);
}

void	ft_exec(char **env)
{
	t_pipex	*p;
	t_pcmd	*head;
	int		i;

	i = 0;
	p = g_sh->pipex;
	head = p->lst;
	while (i < p->nbr_fork)
	{
		ft_pipe(i);
		ft_fork(i);
		if (p->pids[i] == 0)
			ft_child(i, env);
		ft_parent_close(i);
		p->lst = p->lst->next;
		i++;
	}
	p->lst = head;
}
