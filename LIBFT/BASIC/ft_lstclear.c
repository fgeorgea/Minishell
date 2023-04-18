/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:37:45 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/23 10:37:47 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nextclear;
	t_list	*current;

	if (lst == 0 || del == 0)
		return ;
	current = *lst;
	while (current->next)
	{
		nextclear = current->next;
		(del)(current->content);
		free(current);
		current = nextclear;
	}
	(del)(current->content);
	free(current);
	*lst = 0;
}
