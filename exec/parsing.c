/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:43:04 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/08 19:06:02 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	does_cmd_exist(char *str)
{
	if (access(str, F_OK | X_OK) != -1)
		return (1);
	else
		return (0);
}

int	file_exist(char *str)
{
	if (access(str, F_OK) != -1)
		return (1);
	else
		return (0);
}

int	found_cmd(char **cmd)
{
	int		i;
	char	*tmp;
	t_pipex	*p;

	i = 0;
	tmp = NULL;
	p = g_sh->pipex;
	while (p->paths[i])
	{
		tmp = ft_strjoin(p->paths[i], cmd[0]);
		if (!tmp)
			ft_exit(EXIT_MALLOC_FAILURE);
		if (does_cmd_exist(tmp))
		{
			free(cmd[0]);
			cmd[0] = ft_strdup(tmp);
			if (!cmd[0])
				ft_exit(EXIT_MALLOC_FAILURE);
			free(tmp);
			return (1);
		}
		free(tmp);
		if (i == p->nbr_paths - 1)
		{
			if (does_cmd_exist(cmd[0]))
				return (1);
			ft_putstr_fd("Command was not found\n", 2);
			return (0);
		}
		i++;
	}
	return (0);
}
