/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:37:54 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/25 14:03:01 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_pipex(t_pcmd **lst, t_pcmd *new)
{
	t_pcmd	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast_pipex(*lst);
		last->next = new;
	}
}

t_pcmd	*ft_lstlast_pipex(t_pcmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_pipex(t_pcmd **lst)
{
	t_pcmd	*tmp;

	if (!lst || !*lst)
		return ;
	ft_set_lst_head(lst);
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_free_array(tmp->content);
		free(tmp);
	}
}

t_pcmd	*ft_lstnew_pipex(char **content, t_pcmd *previous)
{
	t_pcmd	*list;

	list = malloc(sizeof(t_pcmd));
	if (!list)
	{
		ft_free_array(content);
		ft_error("Failed to create new struct in chained list\n", -1);
	}
	list->content = content;
	list->previous = previous;
	list->next = NULL;
	return (list);
}

void	ft_set_lst_head(t_pcmd **lst)
{
	if (!lst || !*lst)
		return ;
	while ((*lst)->previous)
		*lst = (*lst)->previous;
}
