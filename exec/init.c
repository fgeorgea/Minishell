/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:34 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 15:47:25 by fgeorgea         ###   ########.fr       */
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
		tmp = ft_strjoin_free(p->paths[i], "/");
		if (!tmp)
		{
			ft_free_array_pos((void **)p->paths, i);
			ft_exit(EXIT_MALLOC_FAILURE);
			return ;
		}
		p->paths[i] = ft_strdup_free(tmp);
		if (!p->paths[i])
		{
			ft_free_array_pos((void **)p->paths, i);
			ft_exit(EXIT_MALLOC_FAILURE);
			return ;
		}
		i++;
	}
}

static void	ft_init_paths(t_pipex *p)
{
	char	*paths;
	
	p->nbr_paths = 0;
	paths = get_env_value("PATH", 4);
	if (!paths)
		return ;
	p->paths = ft_split(paths, ':');
	if (!p->paths)
		ft_exit(EXIT_MALLOC_FAILURE);
	p->nbr_paths = ft_arraylen(p->paths);
}

void	ft_init_struct(void)
{
	t_pipex	*p;

	p = g_sh->pipex;
	ft_init_struct_vars(p);
	ft_init_paths(p);
	ft_add_slash(p);
	lst_to_array(&g_sh->env);
	p->pipefd = ft_createpipe_array(p);
	p->pids = ft_createfork_array(p);
}
