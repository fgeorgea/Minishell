/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:39:31 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/23 09:39:34 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == 0)
		return ;
	if (lst[0] == 0)
	{
		lst[0] = new;
		return ;
	}
	last = ft_lstlast(lst[0]);
	last->next = new;
}
