/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:47:36 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/10/14 12:47:38 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t			i;
	unsigned char	*s12;
	unsigned char	*s22;

	if (s1 == 0 || s2 == 0)
		return (0);
	s12 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	if (size == 0)
		return (0);
	size--;
	while (i < size && s12[i] != 0 && s12[i] == s22[i])
		i++;
	return (s12[i] - s22[i]);
}
