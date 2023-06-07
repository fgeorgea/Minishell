/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:46:12 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/08 00:53:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*new_token_list(char *word, t_list *head, char **a, t_list *n)
{
	t_token	*content;
	t_list	*new;

	content = malloc(sizeof(t_token));
	if (!content)
	{
		ft_free_array(a);
		ft_lstclear(&n, &free);
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	content->token = 0;
	content->word = word;
	new = ft_lstnew(content);
	if (!new)
	{
		ft_lstclear(&head, &free_token);
		ft_free_array(a);
		ft_free((void **)&content);
		ft_lstclear(&n, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (new);
}

static t_list	*get_split_space_list(char **arr, t_list *head)
{
	t_list	*new_head;
	t_list	*tmp;
	int		i;

	i = 0;
	new_head = 0;
	while (arr[i])
	{
		tmp = new_token_list(arr[i], head, arr, new_head);
		ft_lstadd_back(&new_head, tmp);
		i++;
	}
	free(arr[i]);
	return (new_head);
}

t_list	*split_space(t_list *curr, t_list *head, t_token **t)
{
	char	**arr;
	t_token	*content;
	t_list	*tmp;
	t_list	*temp;

	content = curr->content;
	arr = shell_split(content->word, "\040\011\012\013\014\015", 0);
	if (!arr)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	tmp = get_split_space_list(arr, head);
	ft_free((void **)&content->word);
	ft_free((void **)&content);
	temp = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = curr->next;
	curr->next = temp->next;
	curr->content = temp->content;
	ft_free((void **)&temp);
	*t = tmp->content;
	return (tmp);
}
