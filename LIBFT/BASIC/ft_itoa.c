/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:26:43 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/18 13:26:45 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_recursive_power(int nb, int power)
{
	if (power == 0)
		return (1);
	else if (power < 0)
		return (-1);
	else
	{
		return (nb * ft_recursive_power(nb, power - 1));
	}
}

static int	ft_set_num(long nb, int i, int power, char *num)
{
	while (power >= 0)
	{
		if (nb / ft_recursive_power(10, power) != 0)
		{
			num[i] = ((nb / ft_recursive_power(10, power)) % 10) + 48;
			i++;
		}
		power--;
	}
	return (i);
}

static int	ft_nblen(long nb)
{
	int	len;

	len = 1;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		i;
	int		power;
	long	nb;

	power = 9;
	i = 0;
	nb = n;
	num = malloc((ft_nblen(nb) + 1));
	if (!num)
		return (0);
	if (nb < 0)
	{
		num[0] = '-';
		nb = -nb;
		i = 1;
	}
	i = ft_set_num(nb, i, power, num);
	if (nb == 0)
	{
		num[0] = '0';
		i++;
	}
	num[i] = 0;
	return (num);
}
