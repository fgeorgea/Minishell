/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_rev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 02:46:21 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/28 04:08:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_array_rev(void **array)
{
	size_t	i;
	size_t	len;
	void	*tmp;

	if (!array || !*array)
		return ;
	i = 0;
	len = ft_arraylen(array);
	while (i < len)
	{
		tmp = array[i];
		array[i] = array[len - 1];
		array[len - 1] = tmp;
		i++;
		len--;
	}
}
