/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:34 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/25 14:21:24 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_slash(t_pipex *p)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (p->paths[i])
	{
		tmp = ft_strjoin(p->paths[i], "/");
		if (!tmp)
			ft_error("Failed to add '/' to cmd path\n", -1);
		free(p->paths[i]);
		p->paths[i] = ft_strdup(tmp);
		if (!p->paths[i])
			ft_error(NULL, -1);
		free(tmp);
		i++;
	}
}

static void	ft_init_paths(t_pipex *p)
{
	char *paths;

	paths = getenv("PATH");
	if (!paths)
		ft_error("Did not find any string with PATH in env\n", 0);
	p->paths = ft_split(paths, ':');
	if (!p->paths)
		ft_error("Failed to create paths array with split\n", -1);
	p->nbr_paths = ft_tablen(p->paths);
}

static void	ft_init_cmds(char **argv, t_pipex *p)
{
	int		i;
	int		cmd_offset;
	char	**tmp;
	t_pcmd	*previous;

	i = 0;
	cmd_offset = 2;
	tmp = NULL;
	previous = NULL;
	if (p->is_heredoc)
		cmd_offset = 3;
	while (i < p->nbr_cmds)
	{
		tmp = ft_split(argv[i + cmd_offset], ' ');
		if (!tmp)
			ft_error("Failed to create commands array with split\n", -1);
		ft_lstadd_back_pipex(&p->lst, ft_lstnew_pipex(tmp, previous));
		previous = p->lst;
		i++;
	}
}

void	ft_init_struct(int argc, char **argv)
{
	t_pipex	*p;
	
	g_sh->pipex = NULL;
	g_sh->pipex = malloc(sizeof(t_pipex));
	if (!g_sh->pipex)
		ft_error("Failed to malloc pipex struct\n", -1);
	p = g_sh->pipex;
	ft_check_here_doc(argc, argv, p);
	ft_init_struct_vars(argc, argv, p);
	ft_init_paths(p);
	ft_add_slash(p);
	ft_init_cmds(argv, p);
	p->pipefd = ft_createpipe_array(p);
	p->pids = ft_createfork_array(p);
}
