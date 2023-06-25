/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:08:51 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 21:07:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks whether there is a '-n' option or not.
static int	is_newline_option(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i] && str[i - 1] == 'n')
		return (1);
	return (0);
}

void	echo_builtin(const char **strs)
{
	int		print_nl;
	size_t	i;

	print_nl = 1;
	i = 0;
	if (!strs || !*strs)
	{
		(void)write(1, "\n", 1);
		return ;
	}
	while (strs[i] && is_newline_option(strs[i]))
	{
		print_nl = 0;
		i++;
	}
	while (strs[i])
	{
		ft_putstr_fd((char *)strs[i], 1);
		if (strs[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (print_nl)
		(void)write(1, "\n", 1);
}
