/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:26:27 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/02 15:27:52 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
    t_redir	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast_redir(*lst);
		last->next = new;
	}
}

t_redir	*ft_lstnew_redir(char *key, int mode)
{
    t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->key = key;
	new->mode = mode;
    new->next = NULL;
	return (new);
}