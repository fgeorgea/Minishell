/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:37 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/25 13:43:39 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(void)
{
	void	*tmp;

	while (g_sh->env)
	{
		if (g_sh->env->key)
			free(g_sh->env->key);
		if (g_sh->env->value)
			free(g_sh->env->value);
		tmp = g_sh->env->next;
		free(g_sh->env);
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
				free(g_sh->cmd->cmd[i]);
				i++;
			}
			free(g_sh->cmd->cmd);
		}
		while (g_sh->cmd->redir)
		{
			if (g_sh->cmd->redir->key)
				free(g_sh->cmd->redir->key);
			tmp = g_sh->cmd->redir->next;
			free(g_sh->cmd->redir);
			g_sh->cmd->redir = tmp;
		}
		tmp = g_sh->cmd->next;
		free(g_sh->cmd);
		g_sh->cmd = tmp;
	}
}

void	ft_free_global(void)
{
	if (g_sh)
	{
		ft_free_cmd();
		ft_free_env();
		free(g_sh);
	}
}
