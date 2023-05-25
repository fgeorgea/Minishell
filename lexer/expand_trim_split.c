/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_trim_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:19:14 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/25 13:19:24 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_split(t_list **curr, t_token *t, t_list *head, int *i)
{
	char	*key;
	char	*value;

	key = get_var_key(t->word, i, head);
	value = get_key_value(key, i, head);
	if (!has_space(value) || i[3])
	{
		if (insert_value(t, key, value, i))
		{
			if (i[4])
				ft_free(value);
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		if (join_value_split(value, curr, i, 0))
		{
			if (i[4])
				ft_free(value);
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
}

void	handle_quotes_etp(t_token *t, int *i)
{
	if (t->word[i[0]] == '\'' && !i[3])
	{
		i[5] = i[0];
		i[0] = skip_quotes(t->word, i[0]);
		i[0] = skip_trim(t->word, i);
	}
	else if (t->word[i[0]] == '"')
	{
		if (i[3])
			i[0] = skip_trim(t->word, i);
		else
			i[5] = i[0];
		if (i[3] || i[0] != skip_quotes(t->word, i[0]))
			i[3] = !i[3];
	}
}

t_list	*ex_trim_split(t_list *curr, t_token *t, t_list *head)
{
	int		i[10];

	i[0] = 0;
	i[3] = 0;
	while (t->word[i[0]])
	{
		if (t->word[i[0]] == '"' || t->word[i[0]] == '\'')
			handle_quotes_etp(t, i);
		else if (t->word[i[0]] == '$' && (ft_isalnum(t->word[i[0] + 1])
				|| t->word[i[0] + 1] == '?' || t->word[i[0] + 1] == '_'
				|| (t->word[i[0] + 1] == '"' && !i[3])))
		{
			expand_split(&curr, t, head, i);
			t = curr->content;
		}
		i[0]++;
	}
	return (curr);
}
