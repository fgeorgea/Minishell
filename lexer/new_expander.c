/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:49:42 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/28 19:48:08 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
i[0] is main index
i[1] is index of $ being expanded
i[2] is index of character after variable key
i[3] is whether inside ""
i[4] is whether to free value
i[5] is index of first "
*/

char	*get_key_value(char *key, int *i, t_list *head)
{
	char	*value;

	if (key[0] == '?' && key[1] == '\0')
	{
		i[4] = 1;
		value = ft_itoa(g_sh->pipe_exit);
		if (!value)
		{
			ft_free((void **)&key);
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else if (key[0] == '0')
	{
		i[4] = 0;
		value = g_sh->name;
	}
	else
	{
		i[4] = 0;
		value = get_env_value(key);
	}
	return (value);
}

void	remove_current_word(t_list **head, t_list **curr, t_list *last)
{
	if (*curr == *head)
	{
		*head = (*curr)->next;
		free_token((*curr)->content);
		ft_free((void **)&*curr);
		*curr = *head;
		return ;
	}
	last->next = (*curr)->next;
	free_token((*curr)->content);
	ft_free((void **)&*curr);
	*curr = last->next;
}

void	update_curr(t_list **head, t_list **curr, t_list **last, t_token *t)
{
	if (!(*t->word) && !t->quotes)
		remove_current_word(head, curr, *last);
	else
	{
		*last = *curr;
		*curr = (*curr)->next;
	}
}

void	expander(t_list **head, t_list *curr)
{
	t_list	*last;
	t_token	*content;
	int		v;

	last = 0;
	while (curr)
	{
		content = curr->content;
		v = has_variable(content->word);
		content->quotes = has_quotes(content->word);
		if (v && content->quotes && is_heredoc(last))
			trim_quotes(content, *head);
		else if (v && content->quotes)
			curr = ex_trim_split(curr, content, *head);
		else if (v && !is_heredoc(last))
		{
			expand(content, *head);
			if (has_space(content->word))
				curr = split_space(curr, *head);
		}
		else if (content->quotes)
			trim_quotes(content, *head);
		update_curr(head, &curr, &last, content);
	}
}
