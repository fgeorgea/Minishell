/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:38:59 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:04:35 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	display_uint(t_conv *conv, unsigned int n, int *count, int big)
{
	if (!(n == 0 && conv->max && conv->max_v == 0))
	{
		if (conv->c == 'u')
			*count += ft_putunbr_base(n, "0123456789", 10);
		else if (conv->c == 'x')
			*count += ft_putunbr_base(n, "0123456789abcdef", 16);
		else
			*count += ft_putunbr_base(n, "0123456789ABCDEF", 16);
	}
	if (conv->min == '-')
		*count += ft_writexchar(conv->min_v - big, ' ');
}

static int	format_uint(t_conv *conv, unsigned int n, int *big, int len)
{
	int	count;

	count = 0;
	if ((conv->c == 'x' || conv->c == 'X') && conv->h && n != 0)
		*big = *big + 2;
	if (conv->min == 1 || (conv->min && conv->min != '-' && conv->max))
		count += ft_writexchar(conv->min_v - *big, ' ');
	if (n && (conv->c == 'x' || conv->c == 'X') && conv->h)
	{
		if (conv->c == 'x')
			write(1, "0x", 2);
		if (conv->c == 'X')
			write(1, "0X", 2);
		count += 2;
	}
	if (conv->min == '0' && !conv->max)
		count += ft_writexchar(conv->min_v - *big, '0');
	if (conv->max && conv->max_v > len)
		count += ft_writexchar(conv->max_v - len, '0');
	return (count);
}

int	convert_uint(t_conv *conv, unsigned int n)
{
	int	count;
	int	len;
	int	big;

	if (conv->c == 'u')
		len = ft_intulen(n, 10);
	else
		len = ft_intulen(n, 16);
	if (n == 0 && conv->max && conv->max_v == 0)
		len = 0;
	big = len;
	if (conv->max && conv->max_v == 0 && n == 0)
		big = 0;
	else if (conv->max && conv->max_v > len)
		big = conv->max_v;
	count = format_uint(conv, n, &big, len);
	display_uint(conv, n, &count, big);
	return (count);
}
