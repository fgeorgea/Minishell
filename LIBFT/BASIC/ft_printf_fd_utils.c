/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:02:55 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 17:27:00 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_printchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

size_t	ft_printstr(char *str, int fd)
{
	size_t	len;

	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write(fd, str, len);
	return (len);
}

void	ft_printhex(unsigned int nb, char *base, size_t *len, int fd)
{
	if (nb < 16)
		*len += ft_printchar(base[nb], fd);
	else
	{
		ft_printhex(nb / 16, base, len, fd);
		ft_printhex(nb % 16, base, len, fd);
	}
}

static void	ft_printhex_ptr(unsigned long int nb, char *base, size_t *len, int fd)
{
	if (nb < 16)
		*len += ft_printchar(base[nb], fd);
	else
	{
		ft_printhex_ptr(nb / 16, base, len, fd);
		ft_printhex_ptr(nb % 16, base, len, fd);
	}
}

size_t	ft_printptr(unsigned long int nb, int fd)
{
	size_t	len;

	len = ft_printstr("0x", fd);
	ft_printhex_ptr(nb, "0123456789abcdef", &len, fd);
	return (len);
}
