/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:00:32 by dpeyrat           #+#    #+#             */
/*   Updated: 2022/10/24 16:02:38 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	size;

	if (str == 0)
		return (0);
	size = ft_strlen(str);
	if (size < len)
		len = size;
	sub = malloc(len + 1);
	if (!sub)
		return (0);
	i = 0;
	while (str[start + i] && i < len && start + i <= size)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
