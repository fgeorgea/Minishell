/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:19:01 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/23 12:19:03 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *))
{
	t_list	*res;
	t_list	*current;
	t_list	*new;

	if (l == 0 || f == 0 || d == 0)
		return (0);
	current = l;
	res = ft_lstnew((f)(current->content));
	if (!res)
		return (0);
	current = current->next;
	while (current)
	{
		new = ft_lstnew((f)(current->content));
		if (!new)
		{
			ft_lstclear(&res, (d));
			return (0);
		}
		ft_lstadd_back(&res, new);
		current = current->next;
	}
	return (res);
}
