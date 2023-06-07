/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_value_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:20:32 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/08 01:01:59 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*word_list_from_arr(char **arr, t_list *head, int i)
{
	t_list	*new;
	t_token	*t;

	i = 0;
	head = 0;
	while (arr[i])
	{
		t = ft_calloc(1, sizeof(t_token));
		if (!t)
		{
			ft_lstclear(&head, &free);
			return (0);
		}
		t->word = arr[i];
		new = ft_lstnew(t);
		if (!new)
		{
			ft_free((void **)&t);
			ft_lstclear(&head, &free);
			return (0);
		}
		ft_lstadd_back(&head, new);
		i++;
	}
	return (head);
}

static int	jfl_free_r(t_token *t, t_list *head, char *tmp2, char *tmp3)
{
	ft_free((void **)&t->word);
	t->word = tmp3;
	t = head->content;
	ft_free((void **)&t->word);
	t->word = tmp2;
	return (0);
}

static int	join_first_last(t_list *head, t_list *curr, int *i, t_list *last)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	t_token	*t;

	t = curr->content;
	tmp = t->word;
	t = head->content;
	tmp[i[1]] = 0;
	tmp2 = ft_strjoin(tmp, t->word);
	if (!tmp2)
	{
		ft_lstclear(&head, &free);
		return (EXIT_MALLOC_FAILURE);
	}
	t = last->content;
	i[0] = ft_strlen(t->word) - 1;
	tmp3 = ft_strjoin(t->word, &tmp[i[2]]);
	if (!tmp3)
	{
		free(tmp2);
		ft_lstclear(&head, &free);
		return (EXIT_MALLOC_FAILURE);
	}
	return (jfl_free_r(t, head, tmp2, tmp3));
}

int	join_value_split(char *value, t_list **curr, int *i, t_token **t)
{
	char	**arr;
	t_list	*new;
	t_list	*tmp;

	arr = shell_split(value, "\040\011\012\013\014\015", 0);
	if (!arr)
		return (EXIT_MALLOC_FAILURE);
	new = word_list_from_arr(arr, 0, 0);
	if (!new)
	{
		ft_free_array(arr);
		return (EXIT_MALLOC_FAILURE);
	}
	ft_free((void **)&arr);
	if (join_first_last(new, *curr, i, ft_lstlast(new)))
		return (EXIT_MALLOC_FAILURE);
	*t = new->content;
	free_token((*curr)->content);
	(*curr)->content = *t;
	tmp = (*curr)->next;
	(*curr)->next = new->next;
	ft_free((void **)&new);
	*curr = ft_lstlast(*curr);
	(*curr)->next = tmp;
	return (EXIT_SUCCESS);
}
