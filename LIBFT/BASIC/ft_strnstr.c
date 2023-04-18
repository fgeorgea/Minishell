/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:49:02 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 17:49:04 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_found(const char *str, const char *find)
{
	int	i;

	i = 0;
	while (str[i] == find[i] && find[i] != 0)
		i++;
	if (find[i] == 0)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	j;
	char	*str2;

	str2 = (char *)str;
	j = 0;
	if (str == 0 || find == 0)
		return (0);
	while (find[j])
		j++;
	if (j == 0)
		return (str2);
	i = 0;
	while (str[i] != 0 && i + j <= n)
	{
		if (ft_found(&str[i], find))
			return (&str2[i]);
		i++;
	}
	return (0);
}
