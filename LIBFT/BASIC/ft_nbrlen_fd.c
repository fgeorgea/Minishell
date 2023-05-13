/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:51:26 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 17:27:09 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_nbrlen(long int nb)
{
	size_t	len;
	int		is_neg;

	is_neg = 0;
	len = 1;
	if (nb < 0)
	{
		is_neg = 1;
		nb *= -1;
	}
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return (len + is_neg);
}
