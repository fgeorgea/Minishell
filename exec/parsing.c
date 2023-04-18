/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:43:04 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/18 14:59:01 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	does_cmd_exist(char *str)
{
	if (access(str, F_OK | X_OK) != -1)
		return (1);
	else
		return (0);
}

static void	put_path_cmd(char **cmd, t_pipex *head, t_global *g)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (g->paths[i])
	{
		tmp = ft_strjoin(g->paths[i], *cmd);
		if (does_cmd_exist(tmp))
		{
			free(*cmd);
			*cmd = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		free(tmp);
		if (i == g->nbr_paths - 1)
		{
			g->lst = head;
			ft_error(g, "Command was not found\n");
		}
		i++;
	}
}

void	ft_parse_cmds(t_global *g)
{
	t_pipex	*head;

	head = g->lst;
	while (g->lst)
	{
		if (!does_cmd_exist(g->lst->content[0]))
			put_path_cmd(&g->lst->content[0], head, g);
		g->lst = g->lst->next;
	}
	g->lst = head;
}
