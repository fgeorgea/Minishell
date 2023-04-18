/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:23:11 by dopeyrat          #+#    #+#             */
/*   Updated: 2022/10/25 12:04:07 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	convert_char(t_conv *conv, int n)
{
	int		count;
	char	c;

	c = (char)n;
	count = 0;
	if (conv->min == '0')
		count += ft_writexchar(conv->min_v - 1, '0');
	else if (conv->min && conv->min != '-')
		count += ft_writexchar(conv->min_v - 1, ' ');
	write(1, &c, 1);
	count++;
	if (conv->min == '-')
		count += ft_writexchar(conv->min_v - 1, ' ');
	return (count);
}

int	convert_percent(t_conv *conv)
{
	if (conv->c != '%')
		return (0);
	return (convert_char(conv, '%'));
}

int	convert_str(t_conv *conv, char *str)
{
	int	len;
	int	count;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (conv->max && len > conv->max_v)
		len = conv->max_v;
	count = len;
	if (conv->min && conv->min != '-' && len < conv->min_v)
		count += ft_writexchar(conv->min_v - len, ' ');
	write(1, str, len);
	if (conv->min == '-' && len < conv->min_v)
		count += ft_writexchar(conv->min_v - len, ' ');
	return (count);
}
