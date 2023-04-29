/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:08:51 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 02:09:03 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_new_line(char *str)
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
	print_nl = 0;
	if (!strs || !strs[0])
	{
		printf("\n");
		return ;
	}
	while (strs[i] && is_new_line(strs[i]))
	{
		print_nl = 1;
		i++;
	}
	while (strs[i])
	{
		printf("%s", strs[i]);
		i++;
	}
	if (print_nl)
		printf("\n");
}
