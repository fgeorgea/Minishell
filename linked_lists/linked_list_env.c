/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:30:10 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/21 18:51:57 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_one_env(t_env *env)
{
	if (!env)
		return ;
	ft_free(env->key);
	ft_free(env->value);
	ft_free(env);
}

int	lstsize_env(t_env **lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *lst;
	if (!lst || !*lst)
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

	if (!lst)
		return ;
	if (!new)
		ft_exit(EXIT_MALLOC_FAILURE);
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
	{
		ft_free(key);
		ft_free(value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
    new->next = NULL;
	return (new);
}