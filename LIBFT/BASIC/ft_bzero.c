/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:29:40 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/17 10:29:42 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *var, size_t n)
{
	size_t			i;
	unsigned char	*var2;

	if (var == 0)
		return ;
	var2 = (unsigned char *)var;
	i = 0;
	while (i < n)
	{
		var2[i] = 0;
		i++;
	}
}
