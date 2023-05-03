/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:46:12 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/03 13:46:22 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_space(t_token *t)
{
	int	i;

	i = 0;
	while (t->word[i])
	{
		if (t->word[i] == '\'' || t->word[i] =='"')
			i = skip_quotes(t->word, i);
		if (ft_iswhitespace(t->word[i]))
			return (1);
		i++;
	}
	return (0);
}

t_list	*split_space(t_list *curr, t_list *head)
{
	char	**arr;
	t_token	*tmp;
	t_list	*temp;
	t_list	*temp2;
	int		i;

	tmp = curr->content;
	arr = shell_split(tmp->word, "\040\011\012\013\014\015");
	if (!arr)
	{
		ft_lstclear(&head, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	i = 1;
	free(tmp->word);
	free(tmp);
	curr->content = 0;
	tmp = malloc(sizeof(t_token));
	if (!tmp)
	{
		ft_lstclear(&head, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	tmp->word = arr[0];
	curr->content = tmp;
	while (arr[i])
	{
		tmp = malloc(sizeof(t_token));
		if (!tmp)
		{
			ft_lstclear(&head, &free);
			ft_free_array(arr);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		tmp->word = arr[i];
		tmp->token = 0;
		temp = ft_lstnew(tmp);
		if (!temp)
		{
			ft_lstclear(&head, &free);
			ft_free_array(arr);
			free(tmp);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		temp2 = curr->next;
		curr->next = temp;
		curr = curr->next;
		curr->next = temp2;
		i++;
	}
	free(arr);
	return (curr->next);
}

void	post_expander(t_list *head)
{
	t_list	*curr;
	t_token	*token;

	curr = head;
	while (curr)
	{
		token = curr->content;
		if (has_space(token))
			curr = split_space(curr, head);
		else
			curr = curr->next;
	}
}