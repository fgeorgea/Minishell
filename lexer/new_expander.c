/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:49:42 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/18 19:26:26 by fgeorgea         ###   ########.fr       */
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

/*int	join_value_split(char *value, t_list **curr, int *i)
{
	t_token	*t;
	char	**arr;
	char	*temp;
	char	*temp2;
	int		j;

	arr = shell_split(value, "\040\011\012\013\014\015", 0);
	if (!arr)
		return (EXIT_MALLOC_FAILURE);
	t = (*curr)->content;
	temp = ft_strndup(t->word, i[1]);
	if (!temp)
	{
		ft_free_array(arr);
		return (EXIT_MALLOC_FAILURE);
	}
	temp2 = ft_strjoin(temp, arr[0]);
	ft_free(temp);
	if (!temp2)
	{
		ft_free_array(arr);
		return (EXIT_MALLOC_FAILURE);
	}
	temp = ft_strdup(&t->word[i[2]]);
	ft_free(t->word);
	t->word = temp2;
	if (!temp)
	{
		ft_free_array(arr);
		return (EXIT_MALLOC_FAILURE);
	}
	j = 1;
	ft_free(arr[0]);
	arr[0] = (char *)(*curr)->next;
	while (arr[j])
	{
		t = ft_calloc(1, sizeof(t_token));
		//if (!t)
		t->word = arr[j];
		(*curr)->next = malloc(sizeof(t_list));
		//if (!(*curr)->next)
		(*curr) = (*curr)->next;
		(*curr)->next = (t_list *)arr[0];
		(*curr)->content = t;
		j++;
	}
	i[0] = ft_strlen(arr[j - 1]);
	t->word = ft_strjoin(arr[j - 1], temp);
	ft_free(arr[j - 1]);
	ft_free(arr);
	ft_free(temp);
	//if (!t->word)
	return (EXIT_SUCCESS);
}*/

t_list	*word_list_from_arr(char **arr, t_list *head, int i)
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
			free(t);
			ft_lstclear(&head, &free);
			return (0);
		}
		ft_lstadd_back(&head, new);
		i++;
	}
	return (head);
}

int	jfl_free_r(t_token *t, t_list *head, char *tmp2, char *tmp3)
{
	free(t->word);
	t->word = tmp3;
	t = head->content;
	free(t->word);
	t->word = tmp2;
	return (0);
}

int	join_first_last(t_list *head, t_list *curr, int *i, t_list *last)
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

int	join_value_split(char *value, t_list **curr, int *i, t_list *new)
{
	char	**arr;
	t_token	*t;
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
	free(arr);
	if (join_first_last(new, *curr, i, ft_lstlast(new)))
		return (EXIT_MALLOC_FAILURE);
	t = new->content;
	free_token((*curr)->content);
	(*curr)->content = t;
	tmp = (*curr)->next;
	(*curr)->next = new->next;
	free(new);
	*curr = ft_lstlast(*curr);
	(*curr)->next = tmp;
	return (EXIT_SUCCESS);
}

char	*get_key_value(char *key, int *i, t_list *head)
{
	char	*value;

	if (key[0] == '?' && key[1] == '\0')
	{
		i[4] = 1;
		value = ft_itoa(g_sh->pipe_exit);
		if (!value)
		{
			ft_free(key);
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		i[4] = 0;
		value = get_env_value(key);
	}
	return (value);
}

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
		else if (t->word[i[0]] == '$' && !ft_iswhitespace(t->word[i[0] + 1])
			&& t->word[i[0] + 1] && (t->word[i[0] + 1] != '"' || !i[3]))
		{
			expand_split(&curr, t, head, i);
			t = curr->content;
		}
		i[0]++;
	}
	return (curr);
}

void	remove_current_word(t_list **head, t_list **curr, t_list *last)
{
	if (*curr == *head)
	{
		*head = (*curr)->next;
		free_token((*curr)->content);
		free(*curr);
		*curr = *head;
		return ;
	}
	last->next = (*curr)->next;
	free_token((*curr)->content);
	free(*curr);
	*curr = last->next;
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
		if (!(*content->word) && !content->quotes)
			remove_current_word(head, &curr, last);
		else
		{
			last = curr;
			curr = curr->next;
		}
	}
}
