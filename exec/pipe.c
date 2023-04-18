/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:57:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/18 14:59:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	*ft_createmini_tab(t_global *g)
{
	int	*tab;

	tab = NULL;
	tab = malloc(sizeof(int) * 2);
	if (!tab)
		ft_error(g, "Failed to create pipe array\n");
	return (tab);
}

int	**ft_createpipe_array(t_global *g)
{
	int	i;
	int	**array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(int *) * (g->nbr_pipe));
	if (!array)
		ft_error(g, "Failed to create pipe array\n");
	while (i < g->nbr_pipe)
	{
		array[i] = ft_createmini_tab(g);
		i++;
	}
	return (array);
}

void	ft_pipe(int pos, t_global *g)
{
	if (pos != g->nbr_fork - 1)
	{
		if (pipe(g->pipefd[pos]) == -1)
			ft_error(g, PIPE_ERR);
	}
}
