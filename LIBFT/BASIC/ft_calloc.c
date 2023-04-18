/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:45:21 by dpeyrat           #+#    #+#             */
/*   Updated: 2022/10/12 14:45:31 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = malloc(count * size);
	if (!temp)
		return (0);
	while (i < size * count)
	{
		temp[i] = 0;
		i++;
	}
	return ((void *)temp);
}
