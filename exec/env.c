/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:24:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/26 17:16:09 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static t_env	*ft_lstlast_env(t_env *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// static void	ft_lstadd_back_env(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	if (!new || !lst)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	else
// 	{
// 		last = ft_lstlast_env(*lst);
// 		last->next = new;
// 	}
// }

// static t_env	*ft_lstnew_env(char *key, char *value)
// {
// 	t_env	*lst;

// 	lst = malloc(sizeof(t_env));
// 	if (!lst)
// 	{
// 		free(key);
// 		free(value);
// 		ft_error("Failed to create new struct in chained list\n", -1);
// 	}
// 	lst->key = key;
// 	lst->value = value;
// 	lst->next = NULL;
// 	return (lst);
// }

int	lstsize_env(t_env **lst)
{
	int		i;
	t_env	*tmp;
	
	i = 1;
	tmp = *lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	*join_key_value(t_env *lst)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(lst->key, "=");
	str = ft_strjoin(tmp, lst->value);
	free(tmp);
	return (str);
}

char	**lst_to_array(t_env **lst)
{
	int		i;
	char	**array;
	int		lstsize;
	t_env	*tmp;
	
	if (!lst)
		return (NULL);
	i = 0;
	lstsize = lstsize_env(lst);
	tmp = *lst;
	array = NULL;
	array = malloc(sizeof(char *) * (lstsize + 1));
	if (!array)
		ft_error("Failed to convert t_env list to array\n", -1);
	while (tmp)
	{
		array[i] = join_key_value(tmp);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
