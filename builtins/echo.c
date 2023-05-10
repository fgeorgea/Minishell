/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:08:51 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/10 12:43:57 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_newline_option(char *str)
{
	int	i;

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

void	ft_echo(char **strs)
{
	int	i;
	int	print_nl;

	i = 0;
	print_nl = 1;
	if (!strs || !strs[0])
	{
		printf("\n");
		return ;
	}
	while (strs[i] && is_newline_option(strs[i]))
	{
		print_nl = 0;
		i++;
	}
	while (strs[i])
	{
		printf("%s ", strs[i]);
		i++;
	}
	if (print_nl)
		printf("\n");
}
