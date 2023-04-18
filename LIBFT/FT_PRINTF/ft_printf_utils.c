/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:26:45 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:03:25 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_intulen(unsigned int n, unsigned int len)
{
	if (n >= len)
		return (1 + ft_intulen(n / len, len));
	return (1);
}

int	ft_putunbr_base(unsigned int n, char *base, unsigned int len)
{
	int	ret;

	if (n < len)
	{
		write(1, &base[n], 1);
		return (1);
	}
	ret = ft_putunbr_base(n / len, base, len);
	return (ret + ft_putunbr_base(n % len, base, len));
}

unsigned int	ft_abs(int n)
{
	if (n > 0)
		return (n);
	return ((unsigned int)-n);
}

int	ft_writexchar(int n, char c)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

int	ft_iscontained(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
