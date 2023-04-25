/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:29:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/25 15:29:59 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(int status)
{
	ft_free_global();
	if (status != EXIT_SUCCESS)
	{
		ft_putstr_fd(g_sh->name, 2);
		write(2, ": ", 2);
	}
	if (status == EXIT_FAILURE)
		ft_putstr_fd("unexpedected error occured\n", 2);
	if (status == EXIT_MALLOC_FAILURE)
		ft_putstr_fd("malloc failure\n", 2);
	exit(status);
}