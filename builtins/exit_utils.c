/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:05:36 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/18 16:13:52 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_white_space(char **arg)
{
	size_t	i;
	char	*new_arg;

	i = 0;
	while (arg[0][i] && arg[0][i] == ' ')
		i++;
	new_arg = ft_strdup(&arg[0][i]);
	if (!new_arg)
		ft_exit(EXIT_MALLOC_FAILURE);
	ft_free(arg[0]);
	arg[0] = new_arg;
}

void	exit_non_numeric_arg(const char *str)
{
	print_err("exit: ", str, ": numeric argument required\n");
	ft_free_global();
	exit(255);
}
