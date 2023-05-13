/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:23:23 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 17:27:15 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_printnbr(long int nb, int fd)
{
	size_t		len;

	if (nb < 0)
	{
		ft_printchar('-', fd);
		ft_printnbr(-nb, fd);
	}
	else if (nb > 9)
	{
		ft_printnbr(nb / 10, fd);
		ft_printnbr(nb % 10, fd);
	}
	else
		ft_printchar(nb + 48, fd);
	len = ft_nbrlen(nb);
	return (len);
}
