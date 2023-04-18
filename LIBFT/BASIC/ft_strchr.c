/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:27:43 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 17:27:45 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	a;
	int				i;
	char			*str2;

	if (str == 0)
		return (0);
	str2 = (char *)str;
	a = c;
	i = 0;
	while (str[i] != 0 && str[i] != a)
	{
		i++;
	}
	if (str[i] == a)
		return (&str2[i]);
	return (0);
}
