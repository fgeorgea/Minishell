/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:41:40 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 17:27:31 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_check_type(va_list ap, char type, size_t *len, int fd)
{
	if (type == 'c')
		*len += ft_printchar(va_arg(ap, int), fd);
	if (type == 's')
		*len += ft_printstr(va_arg(ap, char *), fd);
	if (type == 'p')
		*len += ft_printptr(va_arg(ap, unsigned long int), fd);
	if (type == 'd' || type == 'i')
		*len += ft_printnbr(va_arg(ap, int), fd);
	if (type == 'u')
		*len += ft_printnbr(va_arg(ap, unsigned int), fd);
	if (type == 'x')
		ft_printhex(va_arg(ap, unsigned int), "0123456789abcdef", len, fd);
	if (type == 'X')
		ft_printhex(va_arg(ap, unsigned int), "0123456789ABCDEF", len, fd);
	if (type == '%')
		*len += ft_printchar('%', fd);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	size_t		len;
	int			i;
	va_list		ap;

	len = 0;
	i = 0;
	if (fd < 0 || fd > OPEN_MAX || !str)
		return (-1);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_check_type(ap, str[i + 1], &len, fd);
			i++;
		}
		else
			len += ft_printchar(str[i], fd);
		i++;
	}
	va_end(ap);
	return (len);
}
