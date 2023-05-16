/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:37 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/16 16:13:05 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(void)
{
	void	*tmp;

	while (g_sh->env)
	{
		if (g_sh->env->key)
			ft_free(g_sh->env->key);
		if (g_sh->env->value)
			ft_free(g_sh->env->value);
		tmp = g_sh->env->next;
		ft_free(g_sh->env);
		g_sh->env = tmp;
	}
}

void	ft_free_cmd(void)
{
	void	*tmp;
	int		i;

	while (g_sh->cmd)
	{
		i = 0;
		if (g_sh->cmd->cmd)
		{
			while (g_sh->cmd->cmd[i])
			{
				ft_free(g_sh->cmd->cmd[i]);
				i++;
			}
			ft_free(g_sh->cmd->cmd);
		}
		while (g_sh->cmd->redir)
		{
			if (g_sh->cmd->redir->key)
				ft_free(g_sh->cmd->redir->key);
			tmp = g_sh->cmd->redir->next;
			ft_free(g_sh->cmd->redir);
			g_sh->cmd->redir = tmp;
		}
		tmp = g_sh->cmd->next;
		ft_free(g_sh->cmd);
		g_sh->cmd = tmp;
	}
}

void	free_pipex(void)
{
	t_pipex	*p;

	if (!g_sh->pipex)
		return ;
	p = g_sh->pipex;
	ft_free_array(p->paths);
	ft_free_array(p->env_array);
	ft_free_array_pos((void **)p->pipefd, -1);
	ft_free(p->pids);
	ft_free(p);
	g_sh->pipex = NULL;
}

void	ft_free_global(void)
{
	delete_tmp_file();
	if (g_sh)
	{
		ft_free_cmd();
		ft_free_env();
		free_pipex();
		ft_free(g_sh);
	}
}
