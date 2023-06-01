/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:44:22 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/01 13:26:05 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*t_list	*insert_word_token(t_list *current,
t_list *head, char *str, char **arr)
{
	t_token	*content;
	t_list	*tmp;

	content = malloc(sizeof(t_token));
	if (!content)
	{
		ft_lstclear(&head, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	tmp = malloc(sizeof(t_list));
	if (!tmp)
	{
		ft_free((void **)&content);
		ft_lstclear(&head, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	content->word = str;
	tmp->content = content;
	tmp->next = current->next;
	current->next = tmp;
	return (tmp);
}

t_list	*split_token(t_list *current, t_list *head)
{
	char	**arr;
	t_token	*tmp;
	int		i;

	tmp = current->content;
	arr = shell_split_token(tmp->word, "|<>");
	if (!arr)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	i = 1;
	ft_free((void **)&tmp->word);
	tmp->word = arr[0];
	while (arr[i])
	{
		current = insert_word_token(current, head, arr[i], arr);
		i++;
	}
	ft_free((void **)&arr);
	return (current->next);
}*/

static t_list	*new_node_tokenize(char **arr, t_list *head, int i, t_list *new)
{
	t_list	*tmp;
	t_token	*content;

	content = ft_calloc(1, sizeof(t_token));
	if (!content)
	{
		ft_lstclear(&head, &free_token);
		ft_lstclear(&new, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	tmp = ft_lstnew(content);
	if (!tmp)
	{
		free(content);
		ft_lstclear(&head, &free_token);
		ft_lstclear(&new, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	content->word = arr[i];
	return (tmp);
}

static t_list	*arr_to_list_tokenize(char **arr, t_list *head)
{
	t_list	*new;
	t_list	*tmp;
	int		i;

	i = 0;
	new = 0;
	while (arr[i])
	{
		tmp = new_node_tokenize(arr, head, i, new);
		ft_lstadd_back(&new, tmp);
		i++;
	}
	free(arr);
	return (new);
}

t_list	*split_token(t_list *current, t_list *head)
{
	char	**arr;
	t_token	*tmp;
	t_list	*new;
	t_list	*temp;

	tmp = current->content;
	arr = shell_split_token(tmp->word, "|<>");
	if (!arr)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new = arr_to_list_tokenize(arr, head);
	temp = current->next;
	free_token(tmp);
	current->content = new->content;
	current->next = new->next;
	free(new);
	current = ft_lstlast(current);
	current->next = temp;
	return (current->next);
}

void	tokenize(t_list *head)
{
	t_token	*tmp;
	t_list	*current;

	current = head;
	while (current)
	{
		tmp = current->content;
		if (has_token(tmp))
			current = split_token(current, head);
		else
			current = current->next;
	}
	current = head;
	while (current)
	{
		tmp = current->content;
		if (has_token(tmp))
			tmp->token = 1;
		else
			tmp->token = 0;
		current = current->next;
	}
}
