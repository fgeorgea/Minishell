/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:43:04 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 17:32:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	does_cmd_exist(const char *str)
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

static int	try_cat_path_cmd(char **cmd, size_t pos)
{
	t_pipex	*p;
	char	*str;
	
	p = g_sh->pipex;
	str = ft_strjoin(p->paths[pos], cmd[0]);
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
	if (does_cmd_exist(str))
	{
		ft_free(cmd[0]);
		cmd[0] = ft_strdup(str);
		if (!cmd[0])
			ft_exit(EXIT_MALLOC_FAILURE);
		ft_free(str);
		return (1);
	}
	ft_free(str);
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
			if (does_cmd_exist(cmd[0]))
				return (1);
			ft_printf_fd(2, "Minishell: %s: Command not found\n", cmd[0]);
			return (0);
		}
		i++;
	}
	return (0);
}
