/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:37 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/27 18:02:10 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(void)
{
	void	*tmp;

	while (g_sh->env)
	{
		if (g_sh->env->key)
			ft_free((void **)&g_sh->env->key);
		if (g_sh->env->value)
			ft_free((void **)&g_sh->env->value);
		tmp = g_sh->env->next;
		ft_free((void **)&g_sh->env);
		g_sh->env = tmp;
	}
}

void	ft_free_cmd(void)
{
	void	*tmp;

	while (g_sh->cmd)
	{
		ft_free_array(g_sh->cmd->cmd);
		while (g_sh->cmd->redir)
		{
			if (g_sh->cmd->redir->key)
				ft_free((void **)&g_sh->cmd->redir->key);
			tmp = g_sh->cmd->redir->next;
			ft_free((void **)&g_sh->cmd->redir);
			g_sh->cmd->redir = tmp;
		}
		tmp = g_sh->cmd->next;
		ft_free((void **)&g_sh->cmd);
		g_sh->cmd = tmp;
	}
}

void	free_pipex(void)
{
	t_pipex	*p;

	if (!g_sh->pipex)
		return ;
	p = g_sh->pipex;
	unlink_all_tmp();
	close_all_pipes();
	ft_free_array(p->paths);
	ft_free_array(p->env_array);
	ft_free_array_pos((void **)p->pipefd, -1);
	ft_free((void **)&p->pids);
	ft_free((void **)&p->hd_tmp);
	ft_free((void **)&p);
	g_sh->pipex = NULL;
}

void	ft_free_global(void)
{
	unlink_all_tmp();
	if (g_sh)
	{
		ft_free_cmd();
		ft_free_env();
		free_pipex();
		ft_free((void **)&g_sh->str);
		ft_free((void **)&g_sh);
	}
}
