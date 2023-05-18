/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:43:04 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/18 14:43:57 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	does_cmd_exist(const char *str)
{
	if (access(str, F_OK | X_OK) != -1)
		return (1);
	else
		return (0);
}

int	file_exist(const char *str)
{
	if (access(str, F_OK) != -1)
		return (1);
	else
		return (0);
}

int	try_cat_path_cmd(char **cmd, size_t pos)
{
	t_pipex	*p;
	char	*str;

	p = g_sh->pipex;
	str = ft_strjoin(p->paths[pos], cmd[0]);
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
	if (!does_cmd_exist(str))
	{
		ft_free(str);
		return (0);
	}
	ft_free(cmd[0]);
	cmd[0] = str;
	return (1);
}

int	is_relative_path(const char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	found_cmd(char **cmd)
{
	size_t	i;
	t_pipex	*p;

	i = 0;
	p = g_sh->pipex;
	while (p->paths[i])
	{
		if (try_cat_path_cmd(cmd, i))
			return (1);
		if (i == p->nbr_paths - 1)
		{
			
			if (is_relative_path(cmd[0]) && does_cmd_exist(cmd[0]))
				return (1);
			if (!is_relative_path(cmd[0]))
				print_err(cmd[0], NULL, ": Command not found\n");
			else
				print_err(cmd[0], NULL, ": No such file or directory\n");
			exit(127);
		}
		i++;
	}
	return (0);
}
