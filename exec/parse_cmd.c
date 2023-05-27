/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:43:04 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 01:39:33 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	does_cmd_exist(const char *str)
{
	int	tmp_fd;

	tmp_fd = open((char *)str, O_WRONLY, -1);
	if (tmp_fd == -1 && errno == EISDIR)
	{
		print_err((char *)str, NULL, ": is a directory", 126);
		exit_only_child(126);
		return (0);
	}
	ft_close(&tmp_fd);
	if (access(str, F_OK | X_OK) == -1)
		return (0);
	else
		return (1);
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
		ft_free((void **)&str);
		return (0);
	}
	ft_free((void **)&cmd[0]);
	cmd[0] = str;
	return (1);
}

// Will try to replace cmd with path to cmd if it exists.
int	found_cmd(char **cmd)
{
	size_t	i;
	t_pipex	*p;

	i = 0;
	p = g_sh->pipex;
	if (cmd[0][0] == '\0')
	{
		print_err(cmd[0], NULL, CNF, 127);
		exit(g_sh->pipe_exit);
	}
	while (p->paths && p->paths[i])
	{
		if (try_cat_path_cmd(cmd, i))
			return (1);
		i++;
	}
	try_catch_cmd(cmd);
	return (1);
}
