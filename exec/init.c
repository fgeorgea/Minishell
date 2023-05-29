/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:34 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/29 11:34:54 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Adds a '/' at the end of every PATH strings.
static void	add_slash(t_pipex *p)
{
	size_t	i;
	char	*new_str;

	if (p->nbr_paths == 0)
		return ;
	i = 0;
	while (p->paths[i])
	{
		new_str = ft_strjoin(p->paths[i], "/");
		if (!new_str)
		{
			ft_free_array_pos((void **)p->paths, i);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		ft_free((void **)&p->paths[i]);
		p->paths[i] = new_str;
		i++;
	}
}

//	Splits the PATH env string into an array of strings.
static void	init_paths(t_pipex *p)
{
	char	*paths;

	paths = get_env_value("PATH");
	if (!paths)
		return ;
	p->paths = ft_split(paths, ':');
	if (!p->paths)
		ft_exit(EXIT_MALLOC_FAILURE);
	p->nbr_paths = arraylen((const char **)p->paths);
}

static void	set_base_values(t_pipex *p)
{
	p->paths = NULL;
	p->env_array = NULL;
	p->pids = NULL;
	p->pipefd = NULL;
	p->hd_tmp = NULL;
	g_sh->pipe_exit = 0;
	g_sh->is_exit_lst_cmd = 0;
	p->is_in_child = 0;
	g_sh->here_doc_status = 0;
	p->infile = 0;
	p->outfile = 0;
	p->nbr_paths = 0;
	p->dup_stdin = -1;
	p->dup_stdout = -1;
	g_sh->is_child = PARENT;
	p->nbr_cmds = lstsize_cmd();
	p->nbr_pipe = p->nbr_cmds - 1;
	if (g_sh->cmd->cmd && p->nbr_cmds == 1 && is_builtin(g_sh->cmd->cmd[0]))
		p->nbr_fork = 0;
	else
		p->nbr_fork = p->nbr_cmds;
}

void	init_struct_pipex(void)
{
	t_pipex	*p;

	p = g_sh->pipex;
	set_base_values(p);
	init_paths(p);
	add_slash(p);
	lst_to_array(&g_sh->env);
	p->pipefd = create_pipe_array(p);
	p->pids = create_fork_array(p);
}
