/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:34 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/07 18:38:26 by fgeorgea         ###   ########.fr       */
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
		tmp = ft_strjoin(p->paths[i], "/");
		if (!tmp)
		{
			ft_free_array_pos((void **)p->paths, i);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		free(p->paths[i]);
		p->paths[i] = ft_strdup_free(tmp);
		if (!p->paths[i])
		{
			ft_free_array_pos((void **)p->paths, i);
			ft_exit(EXIT_MALLOC_FAILURE);
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
	p->paths = NULL;
	p->env_array = NULL;
	p->pids = NULL;
	p->pipefd = NULL;
	p->exit_macro = 0;
	p->nbr_cmds = lstsize_cmd();
	p->nbr_pipe = p->nbr_cmds - 1;
	p->nbr_fork = p->nbr_cmds;
	ft_init_paths(p);
	ft_add_slash(p);
	lst_to_array(&g_sh->env);
	p->pipefd = ft_createpipe_array(p);
	p->pids = ft_createfork_array(p);
}
