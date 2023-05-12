/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:44:22 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/02 15:19:12 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_wc(char *str, char *sep)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
		if (is_in_sep(str[i], sep))
			wc++;
		while (is_in_sep(str[i], sep))
			i++;
		if (str[i])
			wc++;
		while (!is_in_sep(str[i], sep) && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				i = skip_quotes(str, i);
			i++;
		}
		if (is_in_sep(str[i], sep))
			wc++;
		while (is_in_sep(str[i], sep))
			i++;
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
		if (is_in_sep(str[i], sep))
		{
			j = i;
			while (is_in_sep(str[i], sep) && str[i])
				i++;
			arr[wc] = ft_strndup(&str[j], i - j);
			if (!arr[wc])
				return (free_split(arr));
			wc++;
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
		if (is_in_sep(str[i], sep))
		{
			j = i;
			while (is_in_sep(str[i], sep) && str[i])
				i++;
			arr[wc] = ft_strndup(&str[j], i - j);
			if (!arr[wc])
				return (free_split(arr));
			wc++;
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
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	i = 1;
	free(tmp->word);
	free(tmp);
	current->content = 0;
	tmp = malloc(sizeof(t_token));
	if (!tmp)
	{
		ft_lstclear(&head, &free_token);
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
			ft_lstclear(&head, &free_token);
			ft_free_array(arr);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		tmp->word = arr[i];
		temp = ft_lstnew(tmp);
		if (!temp)
		{
			ft_lstclear(&head, &free_token);
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
