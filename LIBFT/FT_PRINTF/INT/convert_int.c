/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:38:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:04:48 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void	format_int(t_conv *conv, int n, int *count, int big)
{
	if (conv->min == 1 || (conv->min && conv->min == '0' && conv->max))
		*count += ft_writexchar(conv->min_v - big, ' ');
	if (n < 0)
	{
		write(1, "-", 1);
		(*count)++;
	}
	if (n >= 0 && conv->s)
	{
		write(1, &conv->s, 1);
		(*count)++;
	}
	if (conv->min == '0' && !conv->max)
		*count += ft_writexchar(conv->min_v - big, '0');
}

int	convert_int(t_conv *conv, int n)
{
	int				count;
	int				len;
	unsigned int	nb;
	int				big;

	nb = ft_abs(n);
	len = ft_intulen(nb, 10);
	if (n < 0 || conv->s)
		conv->min_v--;
	big = len;
	if (conv->max && conv->max_v == 0 && n == 0)
		big = 0;
	else if (conv->max && conv->max_v > len)
		big = conv->max_v;
	count = 0;
	format_int(conv, n, &count, big);
	if (conv->max && conv->max_v > len)
		count += ft_writexchar(conv->max_v - len, '0');
	if (!(n == 0 && conv->max && conv->max_v == 0))
		count += ft_putunbr_base(nb, "0123456789", 10);
	if (conv->min == '-')
		count += ft_writexchar(conv->min_v - big, ' ');
	return (count);
}
