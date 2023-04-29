/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:21:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 02:02:39 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_void_array(void **array, int len)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (len == -1)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		return ;
	}
	while (i < len)
	{
		if (array[i])
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
