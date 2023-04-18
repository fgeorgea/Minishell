/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:49:57 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 13:50:45 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (dst == 0 || src == 0)
		return (0);
	i = -1;
	if (dst2 > src2)
	{
		while (len > 0)
		{
			dst2[len - 1] = src2[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			dst2[i] = src2[i];
	}
	return (dst2);
}
