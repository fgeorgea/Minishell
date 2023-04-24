/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:44:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:07:32 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_child(int pos, char **env, t_pipex *p)
{
	if (pos == 0)
		ft_first_child(env, p);
	else if (pos == p->nbr_fork - 1)
		ft_last_child(pos, env, p);
	else
		ft_middle_child(pos, env, p);
}

void	ft_exec(char **env, t_pipex *p)
{
	int		i;
	t_pcmd	*head;

	i = 0;
	head = p->lst;
	while (i < p->nbr_fork)
	{
		ft_pipe(i, p);
		ft_fork(i, p);
		if (p->pids[i] == 0)
			ft_child(i, env, p);
		ft_parent_close(i, p);
		p->lst = p->lst->next;
		i++;
	}
	p->lst = head;
}
