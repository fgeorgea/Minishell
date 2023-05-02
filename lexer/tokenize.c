/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:44:22 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/27 19:44:38 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_token(t_token *t)
{
	int	i;

	i = 0;
	while (t->word[i])
	{
		if (t->word[i] == '\'' || t->word[i] == '"')
			i = skip_quotes(t->word, i);
		if (t->word[i] == '|' || t->word[i] == '<' || t->word[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	get_token_wc(char *str, char *sep)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
		while (is_in_sep(str[i], sep))
		{
			i++;
			wc++;
		}
		if (str[i])
			wc++;
		while (!is_in_sep(str[i], sep) && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				i = skip_quotes(str, i);
			i++;
		}
		while (is_in_sep(str[i], sep))
		{
			wc++;
			i++;
		}
	}
	return (wc);
}

char	**shell_split_token(char *str, char *sep)
{
	char	**arr;
	int		wc;
	int		i;
	int		j;

	wc = get_token_wc(str, sep);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (0);
	i = 0;
	wc = 0;
	while (str[i])
	{
		while (is_in_sep(str[i], sep) && str[i])
		{
			arr[wc] = ft_strndup(&str[i], 1);
			if (!arr[wc])
				return (free_split(arr));
			wc++;
			i++;
		}
		if (str[i])
			j = i;
		else
			break ;
		while (!is_in_sep(str[i], sep) && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				i = skip_quotes(str, i);
			i++;
		}
		arr[wc] = ft_strndup(&str[j], i - j);
		if (!arr[wc])
			return (free_split(arr));
		wc++;
		while (is_in_sep(str[i], sep))
		{
			arr[wc] = ft_strndup(&str[i], 1);
			if (!arr[wc])
				return (free_split(arr));
			wc++;
			i++;
		}
	}
	arr[wc] = 0;
	return (arr);
}

t_list	*split_token(t_list *current, t_list *head)
{
	char	**arr;
	t_token	*tmp;
	t_list	*temp;
	t_list	*temp2;
	int		i;

	tmp = current->content;
	arr = shell_split_token(tmp->word, "|<>");
	if (!arr)
	{
		ft_lstclear(&head, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	i = 1;
	free(tmp->word);
	free(tmp);
	current->content = 0;
	tmp = malloc(sizeof(t_token));
	if (!tmp)
	{
		ft_lstclear(&head, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	tmp->word = arr[0];
	current->content = tmp;
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
		temp = ft_lstnew(tmp);
		if (!temp)
		{
			ft_lstclear(&head, &free);
			ft_free_array(arr);
			free(tmp);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		temp2 = current->next;
		current->next = temp;
		current = current->next;
		current->next = temp2;
		i++;
	}
	free(arr);
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