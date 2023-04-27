/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:27:39 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/27 14:31:00 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_struct_vars(t_pipex *p)
{
	p->paths = NULL;
	p->pids = NULL;
	p->pipefd = NULL;
	p->end_token = NULL;
	p->nbr_cmds = lstsize_cmd(&g_sh->cmd);
	p->nbr_pipe = p->nbr_cmds - 1;
	p->nbr_fork = p->nbr_cmds;
}
