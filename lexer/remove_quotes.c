/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/04 19:49:54 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_quotes(t_token *t)
{
	int	i;

	i = 0;
	while (t->word[i])
	{
		if (t->word[i] == '\'' || t->word[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	trim_quotes(t_token *t, t_list *head)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	while (t->word[i])
	{
		if (t->word[i] == '"' || t->word[i] == '\'')
		{
			j = skip_quotes(t->word, i);
			if (i == j)
				return ;
			tmp = malloc(sizeof(char) * (ft_strlen(t->word) - 1));
			if (!tmp)
			{
				ft_lstclear(&head, &free_token);
				ft_exit(EXIT_MALLOC_FAILURE);
			}
			k = 0;
			while (k < i)
			{
				tmp[k] = t->word[k];
				k++;
			}
			while (k + 1 < j)
			{
				tmp[k] = t->word[k + 1];
				k++;
			}
			while (t->word[k + 2])
			{
				tmp[k] = t->word[k + 2];
				k++;
			}
			tmp[k] = 0;
			free(t->word);
			t->word = tmp;
			i = j - 2;
		}
		i++;
	}
}

void	remove_quotes(t_list *head)
{
	t_list	*current;
	t_token	*tmp;
	char	*hold;

	current = head;
	while (current)
	{
		tmp = current->content;
		if (has_quotes(tmp))
		{
			tmp->quotes = 1;
			trim_quotes(tmp, head);
			if (tmp->pre_exp)
			{
				hold = tmp->word;
				
			}
		}
		else
			tmp->quotes = 0;
		current = current->next;
	}
}