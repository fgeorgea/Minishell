/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:34 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/27 14:29:39 by fgeorgea         ###   ########.fr       */
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
	t_env	*tmp;
	
	tmp = g_sh->env;
	while (tmp && (ft_strncmp(tmp->key, "PATH", 4) != 0))
		tmp = tmp->next;
	if (ft_strncmp(tmp->key, "PATH", 4) != 0)
		ft_error("Did not find any PATH in the env\n", 0);
	p->paths = ft_split(tmp->value, ':');
	if (!p->paths)
		ft_error("Did not find any string with PATH in env\n", -1);
	p->nbr_paths = ft_tablen(p->paths);
}

// static void	ft_init_cmds(char **argv, t_pipex *p)
// {
// 	int		i;
// 	int		cmd_offset;

// 	i = 0;
// 	cmd_offset = 2;
// 	if (p->is_heredoc)
// 		cmd_offset = 3;
// 	while (i < p->nbr_cmds)
// 	{
// 		ft_lstadd_back_env(&p->lst, ft_lstnew_env(tmp));
// 		i++;
// 	}
// }

void	ft_init_struct(void)
{
	t_pipex	*p;

	p = g_sh->pipex;
	ft_init_struct_vars(p);
	ft_init_paths(p);
	ft_add_slash(p);
	//ft_init_cmds(argv, p);
	p->env_array = lst_to_array(&g_sh->env);
	p->pipefd = ft_createpipe_array(p);
	p->pids = ft_createfork_array(p);
}
