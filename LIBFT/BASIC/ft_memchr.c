/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:07:36 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 16:07:38 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*str2;
	void			*str3;

	if (str == 0)
		return (0);
	str2 = (unsigned char *)str;
	a = c;
	i = 0;
	while (i < n)
	{
		if (str2[i] == a)
		{
			str3 = (void *)str2;
			return (&str3[i]);
		}
		i++;
	}
	return (0);
}
