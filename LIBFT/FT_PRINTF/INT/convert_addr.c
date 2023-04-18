/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:59:45 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:04:23 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_intulllen(unsigned long long n, unsigned long long len)
{
	if (n >= len)
		return (1 + ft_intulllen(n / len, len));
	return (1);
}

int	ft_putullnbr_base(unsigned long long n, char *base, unsigned long long len)
{
	int	ret;

	if (n < len)
	{
		write(1, &base[n], 1);
		return (1);
	}
	ret = ft_putullnbr_base(n / len, base, len);
	return (ret + ft_putullnbr_base(n % len, base, len));
}

int	convert_addr(t_conv *conv, unsigned long long n)
{
	int	count;
	int	len;

	len = 2 + ft_intulllen(n, 16);
	if (n == 0 && conv->max && conv->max_v == 0)
		len = 2;
	count = 0;
	if (conv->min && conv->min != '-')
		count += ft_writexchar(conv->min_v - len, ' ');
	write(1, "0x", 2);
	count += 2;
	if (!(n == 0 && conv->max && conv->max_v == 0))
		count += ft_putullnbr_base(n, "0123456789abcdef", 16);
	if (conv->min == '-')
		count += ft_writexchar(conv->min_v - len, ' ');
	return (count);
}
