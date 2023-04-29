/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:57:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 02:06:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe(int pos)
{
	t_pipex	*p;

	p = g_sh->pipex;
	if (pos == p->nbr_fork - 1)
		return ;
	if (pipe(p->pipefd[pos]) == -1)
		ft_exit(EXIT_PIPE_FAILURE);
}

static int	*ft_createmini_tab(void)
{
	int	*tab;

	tab = NULL;
	tab = malloc(sizeof(int) * 2);
	if (!tab)
		ft_exit(EXIT_MALLOC_FAILURE);
	return (tab);
}

int	**ft_createpipe_array(t_pipex *p)
{
	int		i;
	int		**array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(int *) * (p->nbr_pipe));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	while (i < p->nbr_pipe)
	{
		array[i] = ft_createmini_tab();
		i++;
	}
	return (array);
}
