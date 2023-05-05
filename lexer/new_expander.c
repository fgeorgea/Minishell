/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:49:42 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/05 14:49:52 by dopeyrat         ###   ########.fr       */
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

int	join_value_split(char *key, char *value, t_list **curr, int *i)
{
	
}

void	expand_split(t_list **curr, t_token *t, t_list *head, int *i)
{
	char	*key;
	char	*value;

	key = get_var_key(t->word, i, head);
	if (key[0] == '?' && key[1] == '\0')
	{
		i[4] = 1;
		value = ft_itoa(g_sh->pipe_exit);
		if (!value)
		{
			free(key);
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		i[4] = 0;
		value = get_env_value(key, ft_strlen(key));
	}
	if (!has_space(value) || i[3])
	{
		if (insert_value(t, key, value, i))
		{
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		if (join_value_split(key, value, curr, i))
		{
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
}

t_list	*ex_trim_split(t_list *curr, t_token *t, t_list *head)
{
	int		i[10];

	i[0] = 0;
	i[3] = 0;
	while (t->word[i[0]])
	{
		if (t->word[i[0]] == '\'' && !i[3])
			i[0] = skip_trim(t->word, i[0]);
		else if (t->word[i[0]] == '"')
		{
			if (!i[3])
				i[5] = i[0];
			else
				i[0] = skip_trim(t->word, i[0]);
			i[3] = !i[3];
		}
		else if (t->word[i[0]] == '$' && !ft_iswhitespace(t->word[i[0] + 1]) && t->word[i[0] + 1])
		{
			expand_split(&curr, t, head, i);
			t = curr->content;
		}
		i[0]++;
	}
	return (curr);
}

void	expander(t_list *head)
{
	t_list	*curr;
	t_list	*last;
	t_token	*content;
	int		v;
	char	*hold;

	curr = head;
	last = 0;
	while (curr)
	{
		content = curr->content;
		v = has_variable(content->word);
		content->quotes = has_quotes(content->word);
		if (v && content->quotes)
		{
			if (is_heredoc(last))
				trim_quote(content, head);
			else
				curr = ex_trim_split(curr, content, head);
		}
		else if (v)
		{
			expand(content, head);
			if (has_space(content->word))
				curr = split_splace(curr, head);
		}
		else if (content->quotes)
			trim_quote(content, head);
		last = curr;
		curr = curr->next;
	}
}