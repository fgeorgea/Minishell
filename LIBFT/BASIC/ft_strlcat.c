/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:14:49 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 17:14:52 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*src2;
	int		temp;

	if (dst == 0 || src == 0)
		return (0);
	src2 = (char *)src;
	temp = ft_strlen(dst);
	i = 0;
	j = temp;
	if (j >= n)
		return (n + ft_strlen(src2));
	while (src2[i] != 0 && j < (n - 1))
	{
		dst[j] = src2[i];
		i++;
		j++;
	}
	dst[j] = 0;
	return (temp + ft_strlen(src2));
}
