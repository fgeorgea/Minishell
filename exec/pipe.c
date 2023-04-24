/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:57:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:16:47 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*ft_createmini_tab(t_pipex *p)
{
	int	*tab;

	tab = NULL;
	tab = malloc(sizeof(int) * 2);
	if (!tab)
		ft_error(p, "Failed to create pipe array\n", -1);
	return (tab);
}

int	**ft_createpipe_array(t_pipex *p)
{
	int	i;
	int	**array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(int *) * (p->nbr_pipe));
	if (!array)
		ft_error(p, "Failed to create pipe array\n", -1);
	while (i < p->nbr_pipe)
	{
		array[i] = ft_createmini_tab(p);
		i++;
	}
	return (array);
}

void	ft_pipe(int pos, t_pipex *p)
{
	if (pos != p->nbr_fork - 1)
	{
		if (pipe(p->pipefd[pos]) == -1)
			ft_error(p, PIPE_ERR, -1);
	}
}
