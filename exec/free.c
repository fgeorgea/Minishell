/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:21:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/11 18:33:03 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array_pos(void **array, int pos)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	if (pos == -1)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	else
	{
		while (i < pos)
		{
			if (array[i])
				free(array[i]);
			i++;
		}	
	}
	free(array);
	array = NULL;
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	delete_tmp_file(void)
{
	if (access(TMP_FILE, F_OK) != -1)
		unlink(TMP_FILE);
}
