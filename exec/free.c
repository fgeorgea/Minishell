/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:21:35 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 01:54:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Sets pointer to NULL after being freed.
void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

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
			ft_free((void **)&array[i]);
			i++;
		}
	}
	else
	{
		while (i < pos)
		{
			if (array[i])
				ft_free((void **)&array[i]);
			i++;
		}	
	}
	ft_free((void **)&array);
}

void	ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i])
	{
		ft_free((void **)&array[i]);
		i++;
	}
	ft_free((void **)&array);
}

// Delete heredoc tmp file.
void	delete_tmp_file(char *file)
{
	if (access(file, F_OK) != -1)
		unlink(file);
}
