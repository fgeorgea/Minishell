/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 15:25:58 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child(int pos, char **env, t_global *g)
{
	if (pos == 0)
		ft_first_child(env, g);
	else if (pos == g->nbr_fork - 1)
		ft_last_child(pos, env, g);
	else
		ft_middle_child(pos, env, g);
}

void	ft_exec(char **env, t_global *g)
{
	int		i;
	t_pipex	*head;

	i = 0;
	head = g->lst;
	while (i < g->nbr_fork)
	{
		ft_pipe(i, g);
		ft_fork(i, g);
		if (g->pids[i] == 0)
			ft_child(i, env, g);
		ft_parent_close(i, g);
		g->lst = g->lst->next;
		i++;
	}
	g->lst = head;
}
