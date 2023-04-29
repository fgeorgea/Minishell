/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:24:03 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 01:51:45 by fgeorgea         ###   ########.fr       */
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

char	*get_env_value(char *key_to_find, int size)
{
	t_env	*env;
	
	env = g_sh->env;
	while (env && (ft_strncmp(env->key, key_to_find, size) != 0))
		env = env->next;
	if (ft_strncmp(env->key, key_to_find, size) != 0)
		return (NULL);
	return (env->value);
}

int	lstsize_env(t_env **lst)
{
	int		i;
	t_env	*tmp;
	
	i = 1;
	tmp = *lst;
	if (!lst)
		ft_error("There are no environments\n", 0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	lstsize_cmd(t_cmd **lst)
{
	int		i;
	t_cmd	*tmp;
	
	i = 1;
	tmp = *lst;
	if (!lst)
		ft_error("There are no commands\n", 0);
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
	array = malloc(sizeof(char *) * (lstsize + 1));
	if (!array)
		ft_exit(EXIT_MALLOC_FAILURE);
	while (tmp)
	{
		array[i] = join_key_value(tmp);
		if (!array[i])
			ft_exit(EXIT_MALLOC_FAILURE);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
