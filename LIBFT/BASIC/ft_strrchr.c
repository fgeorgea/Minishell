/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:31:53 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 17:31:56 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	a;
	int				i;
	char			*str2;

	if (str == 0)
		return (0);
	str2 = (char *)str;
	a = c;
	i = 0;
	while (str[i])
		i++;
	while (i >= 0 && str[i] != a)
		i--;
	if (i < 0)
		return (0);
	return (&str2[i]);
}
