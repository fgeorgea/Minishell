/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 16:22:32 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if there is only 1 (digit only) arg.
static int	is_valid_exit(const char **args)
{
	size_t	i;

	i = 1;
	if (!ft_isdigit(args[0][0]) && args[0][0] != '-')
		exit_non_numeric_arg(args[0]);
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
			exit_non_numeric_arg(args[0]);
		i++;
	}
	if (arraylen(args) > 1)
	{
		print_err("exit: ", NULL, "too many arguments", 1);
		return (0);
	}
	return (1);
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

static long int	ft_atol(const char *str)
{
	int			is_neg;
	long int	nbr;

	is_neg = 1;
	if (!str)
		return (0);
	is_neg = 1;
	nbr = 0;
	str = ft_getsign(str, &is_neg);
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str - 48;
		str++;
	}
	return (nbr * is_neg);
}

// Checks if the exit arg overflows LONG MIN/MAX.
static int	has_overflow(const char *str)
{
	int		arg_len;
	char	*long_max;
	char	*long_min;

	long_max = "9223372036854775807";
	long_min = "-9223372036854775808";
	arg_len = ft_strlen(str);
	if (str[0] != '-')
	{
		if (arg_len > 19)
			return (1);
		if ((ft_strncmp(str, long_max, 19) > 0) && arg_len == 19)
			return (1);
	}
	if (str[0] == '-')
	{
		if (arg_len > 20)
			return (1);
		if ((ft_strncmp(str, long_min, 20) > 0) && arg_len == 20)
			return (1);
	}
	return (0);
}

void	exit_builtin(const char **arg)
{
	long int	status;

	status = 0;
	ft_putstr_fd("exit\n", 2);
	if (!arg || !*arg)
		ft_exit(0);
	skip_white_space((char **)arg);
	if (!is_valid_exit(arg))
		return ;
	if (has_overflow((arg[0])))
		exit_non_numeric_arg(arg[0]);
	status = ft_atol(arg[0]);
	ft_free_global();
	exit((unsigned char)status);
}
