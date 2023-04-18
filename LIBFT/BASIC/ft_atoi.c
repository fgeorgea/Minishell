/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:08:58 by dpeyrat           #+#    #+#             */
/*   Updated: 2022/10/24 15:43:03 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_check_overflow(unsigned long result, int mcount)
{
	if (result == 0)
		return (1);
	if (result > 9223372036854775807 && mcount == 1)
		return (-1);
	else if (result - 1 > 9223372036854775807 && mcount == -1)
		return (0);
	return (1);
}

static int	check_overflow_len(const char *str, size_t n, int mcount)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[n + j] == '0')
		j++;
	while (str[n + i + j] >= '0' && str[n + i + j] <= '9')
		i++;
	if (i >= 20)
	{
		if (mcount == 1)
			return (-1);
		return (0);
	}
	return (1);
}

static int	construct_num(const char *str, size_t i, int mcount)
{
	unsigned long	result;
	int				ret;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		ret = ft_check_overflow(result, mcount);
		if (ret != 1)
			return (ret);
		i++;
	}
	return ((int)result * mcount);
}

int	ft_atoi(const char *str)
{
	size_t			i;
	int				mcount;
	int				ret;

	if (str == 0)
		return (0);
	i = 0;
	mcount = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mcount = -1;
		i++;
	}
	ret = check_overflow_len(str, i, mcount);
	if (ret != 1)
		return (ret);
	return (construct_num(str, i, mcount));
}
