/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:14:42 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 16:14:43 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;
	unsigned char	*s12;
	unsigned char	*s22;

	if (s1 == 0 || s2 == 0)
		return (0);
	s12 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s12[i] == s22[i] && i < n - 1)
		i++;
	a = s12[i];
	b = s22[i];
	return (a - b);
}
