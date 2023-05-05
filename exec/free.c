/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:21:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/05 15:47:58 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array_pos(void **array, int pos)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i] && pos == -1)
	{
		free(array[i]);
		i++;
	}
	while (i < pos && pos != -1)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
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
}

void	delete_tmp_file(void)
{
	if (access(TMP_FILE, F_OK) != -1)
		unlink(TMP_FILE);
}
