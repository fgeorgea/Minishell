/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:05:33 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/18 18:05:35 by dpeyrat          ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	char	num[13];
	int		i;
	int		power;
	long	nb;

	power = 9;
	i = 0;
	nb = n;
	if (nb < 0)
	{
		num[0] = '-';
		nb = -nb;
		i = 1;
	}
	if (nb == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	i = ft_set_num(nb, i, power, num);
	write(fd, &num, i);
}
