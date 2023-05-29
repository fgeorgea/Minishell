/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:12:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/29 11:06:01 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	does_cmd_exist_underscore(const char *str)
{
	int	tmp_fd;

	tmp_fd = open((char *)str, O_WRONLY, -1);
	if (tmp_fd == -1 && errno == EISDIR)
		return (0);
	ft_close(&tmp_fd);
	if (access(str, F_OK | X_OK) == -1)
		return (0);
	else
		return (1);
}

int	try_cat_path_cmd_underscore(char **cmd, size_t pos)
{
	t_pipex	*p;
	char	*str;

	p = g_sh->pipex;
	str = ft_strjoin(p->paths[pos], cmd[0]);
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
	if (!does_cmd_exist_underscore(str))
	{
		ft_free((void **)&str);
		return (0);
	}
	ft_free((void **)&cmd[0]);
	cmd[0] = str;
	return (1);
}
