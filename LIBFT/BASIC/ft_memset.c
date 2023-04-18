/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:18:40 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 10:18:41 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*str2;

	if (str == 0)
		return (0);
	str2 = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		str2[i] = (unsigned char)c;
		i++;
	}
	return ((void *)str);
}
