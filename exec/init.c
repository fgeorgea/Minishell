/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:34 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/04 14:10:52 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_slash(t_pipex *p)
{
	int		i;
	char	*tmp;

	i = 0;
	while (p->paths[i])
	{
		tmp = ft_strjoin_exit(p->paths[i], "/");
		free(p->paths[i]);
		p->paths[i] = ft_strdup_exit(tmp);
		free(tmp);
		i++;
	}
}

static void	ft_init_paths(t_pipex *p)
{
	char	*paths;
	char	*tmp;
	
	tmp = get_env_value("PATH", 4);
	paths = ft_strtrim(tmp, "\"");
	free(tmp);
	p->paths = ft_split_exit(paths, ':');
	if (!p->paths)
		ft_putstr_fd("No such file or directory\n", 2);
	p->nbr_paths = ft_arraylen(p->paths);
}

void	ft_init_struct(void)
{
	t_pipex	*p;

	p = g_sh->pipex;
	ft_init_struct_vars(p);
	ft_init_paths(p);
	ft_add_slash(p);
	p->env_array = lst_to_array(&g_sh->env);
	p->pipefd = ft_createpipe_array(p);
	p->pids = ft_createfork_array(p);
}
