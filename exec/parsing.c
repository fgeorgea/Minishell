/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:43:04 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 01:26:30 by fgeorgea         ###   ########.fr       */
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

void	check_cmd(char **cmd)
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
			return ;
		}
		free(tmp);
		if (i == p->nbr_paths - 1)
		{
			if (does_cmd_exist(cmd[0]))
				return ;
			ft_putstr_fd("Command was not found\n", 2);
			exit(0);
		}
		i++;
	}
}
