/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/12 02:37:25 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_exit(const char **args)
{
	size_t	i;
	size_t	array_len;

	array_len = arraylen(args);
	if (array_len > 1)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (0);
	}
	i = 0;
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
		{
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd((char *)args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_free_global();
			exit(255);
		}
		i++;
	}
	return (1);
}

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

void	exit_builtin(const char **arg)
{
	long long int	status;

	status = 0;
	if (!arg || !*arg)
		ft_exit(status);
	if (!is_valid_exit(arg))
		return ;
	status = ft_atolli(arg[0]);
	ft_free_global();
	exit((unsigned char)status);
}
