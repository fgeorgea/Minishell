/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/11 18:54:00 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

static const char	*ft_getsign(const char *str, int *is_neg)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*is_neg *= -1;
		str++;
	}
	return (str);
}

static long long int	ft_atolli(const char *str)
{
	int				is_neg;
	long long int	nbr;
	long long int	tmp;

	is_neg = 1;
	if (!str)
		return (0);
	is_neg = 1;
	nbr = 0;
	tmp = 0;
	while (ft_isspace(*str))
		str++;
	str = ft_getsign(str, &is_neg);
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str - 48;
		if (nbr < tmp && is_neg == 1)
			return (-1);
		if (nbr < tmp && is_neg == -1)
			return (0);
		tmp = nbr;
		str++;
	}
	return (nbr * is_neg);
}

void	ft_exit_builtin(char **arg)
{
	int				array_len;
	long long int	status;

	array_len = arraylen(arg);
	if (array_len > 1)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return ;
	}
	status = 0;
	if (!arg || !*arg)
		ft_exit(status);
	status = ft_atolli(arg[0]);
	ft_free_global();
	exit((unsigned char)status);
}
