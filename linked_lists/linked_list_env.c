/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:30:10 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/04 17:45:06 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize_env(t_env **lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *lst;
	if (!lst)
		return (0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
    t_env	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
}

t_env	*ft_lstnew_env(char *key, char *value)
{
    t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
    new->next = NULL;
	return (new);
}