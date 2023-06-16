/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:57:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/16 16:33:23 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Protected version of pipe function.
int	ft_pipe(size_t pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	if (pos == p->nbr_pipe)
		return (1);
	if (pipe(p->pipefd[pos]) == -1)
		return (0);
	return (1);
}

static int	*createmini_tab(void)
{
	int	*array;

	array = malloc(sizeof(int) * 2);
	if (!array)
		return (NULL);
	array[0] = -1;
	array[1] = -1;
	return (array);
}

int	**create_pipe_array(const t_pipex *p)
{
	size_t	i;
	int		**array;

	i = 0;
	if (p->nbr_pipe == 0)
		return (NULL);
	array = malloc(sizeof(int *) * (p->nbr_pipe + 1));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	while (i < p->nbr_pipe)
	{
		array[i] = createmini_tab();
		if (!array[i])
		{
			ft_free_array_pos((void **)array, i);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	close_all_pipes(void)
{
	t_pipex	*p;
	size_t	i;

	i = 0;
	p = g_sh->pipex;
	if (!p->pipefd || !*p->pipefd)
		return ;
	while (p->pipefd[i])
	{
		ft_close(&p->pipefd[i][0]);
		ft_close(&p->pipefd[i][1]);
		i++;
	}
}
