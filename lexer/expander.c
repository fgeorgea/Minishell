/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:23:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/02 16:28:46 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_variable(t_token *t)
{
	int	i;

	i = 0;
	while (t->word[i])
	{
		if (t->word[i] == '\'')
			i = skip_quotes(t->word, i);
		if (t->word[i] == '$' && t->word[i + 1] && t->word[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	expand(t_token *t, t_list *head)
{
	char	*value;
	char	*tmp;
	int		i;
	int		j[3];
	int		len;

	i = 0;
	len = 0;
	j[2] = 0;
	while (t->word[i])
	{
		if (t->word[i] == '"')
			j[2] = !j[2];
		if (t->word[i] == '\'' && !j[2])
			i = skip_quotes(t->word, i);
		if (t->word[i] == '$' && t->word[i + 1] && t->word[i + 1] != ' ')
		{
			j[0] = i;
			while (t->word[i] && t->word[i] != ' ')
			{
				if ((t->word[i] == '\'' || t->word[i] == '"') && !j[2])
					i = skip_quotes(t->word, i);
				else if (t->word[i] == '"')
					j[2] = !j[2];
				i++;
			}
			j[1] = i;
			len = ft_strlen(&t->word[i]);
			break ;
		}
		i++;
	}
	tmp = ft_strndup(&t->word[j[0] + 1], j[1] - j[0]);
	if (!tmp)
	{
		ft_lstclear(&head, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	value = get_env_value(tmp, ft_strlen(tmp));
	free(tmp);
	tmp = malloc(sizeof(char) * (ft_strlen(value) + i + len + 1));
	if (!tmp)
	{
		ft_lstclear(&head, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	i = 0;
	while (i < j[0])
	{
		tmp[i] = t->word[i];
		i++;
	}
	j[0] = 0;
	while (value && value[j[0]])
	{
		tmp[i + j[0]] = value[j[0]];
		j[0]++;
	}
	i += j[0];
	j[0] = 0;
	while (j[0] < len)
	{
		tmp[i + j[0]] = t->word[j[1] + j[0]];
		j[0]++;
	}
	tmp[i + j[0]] = 0;
	free(t->word);
	t->word = tmp;
}

void	expander(t_list *head)
{
	t_list	*curr;
	t_token	*tmp;

	curr = head;
	while (curr)
	{
		tmp = curr->content;
		if (has_variable(tmp))
			expand(tmp, head);
		else
			curr = curr->next;
	}
}