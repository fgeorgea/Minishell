/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:05:36 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/19 14:10:33 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Skips the ' ' and '+'
void	skip_white_space(char **arg)
{
	size_t	i;
	char	*new_arg;

	i = 0;
	while (arg[0][i] && arg[0][i] == ' ')
		i++;
	if (arg[0][i] && arg[0][i] == '+')
		i++;
	new_arg = ft_strdup(&arg[0][i]);
	if (!new_arg)
		ft_exit(EXIT_MALLOC_FAILURE);
	ft_free(arg[0]);
	arg[0] = new_arg;
}

// Exits the program if the first arg is non numeric.
void	exit_non_numeric_arg(const char *str)
{
	print_err("exit: ", (char *)str, ": numeric argument required", 255);
	ft_free_global();
	exit(255);
}
