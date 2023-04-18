/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:38:12 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:03:16 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	init_conv(t_conv *conv)
{
	conv->c = 0;
	conv->s = 0;
	conv->h = 0;
	conv->min = 0;
	conv->min_v = 0;
	conv->max = 0;
	conv->max_v = 0;
	conv->i = 0;
	conv->count = 0;
}

void	reset_conv(t_conv *conv)
{
	conv->c = 0;
	conv->s = 0;
	conv->h = 0;
	conv->min = 0;
	conv->min_v = 0;
	conv->max = 0;
	conv->max_v = 0;
}

int	convert_va(const char *str, int *i, t_conv *conv)
{
	(*i)++;
	get_conv(str, i, conv);
	if (conv->c == 'c')
		return (convert_char(conv, va_arg(conv->ap, int)));
	if (conv->c == 's')
		return (convert_str(conv, va_arg(conv->ap, char *)));
	if (conv->c == 'd' || conv->c == 'i')
		return (convert_int(conv, va_arg(conv->ap, int)));
	if (conv->c == 'u' || conv->c == 'x' || conv->c == 'X')
		return (convert_uint(conv, va_arg(conv->ap, unsigned int)));
	if (conv->c == 'p')
		return (convert_addr(conv, va_arg(conv->ap, unsigned long long)));
	return (convert_percent(conv));
}

int	ft_printf(const char *str, ...)
{
	t_conv	conv;

	if (!str)
		return (-1);
	init_conv(&conv);
	va_start(conv.ap, str);
	while (str[conv.i])
	{
		if (str[conv.i] != '%')
		{
			write(1, &str[conv.i], 1);
			conv.i++;
			conv.count++;
		}
		else
		{
			conv.count += convert_va(str, &conv.i, &conv);
			reset_conv(&conv);
		}
	}
	va_end(conv.ap);
	return (conv.count);
}
