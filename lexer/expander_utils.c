/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:15:27 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/19 14:13:23 by fgeorgea         ###   ########.fr       */
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

int	has_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	has_variable(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !q)
			i = skip_quotes(str, i);
		if (str[i] == '"')
			q = !q;
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var_key(char *str, int *i, t_list *head)
{
	char	*tmp;

	i[1] = i[0];
	i[0]++;
	if (!ft_isdigit(str[i[0]]))
	{
		while (ft_isalnum(str[i[0]]) || str[i[0]] == '_')
			i[0]++;
	}
	if (i[1] + 1 == i[0] && (ft_isdigit(str[i[0]]) || str[i[0]] == '?'))
		i[2] = i[0] + 1;
	else
		i[2] = i[0];
	tmp = ft_strndup(&str[i[1] + 1], i[2] - i[1] - 1);
	if (!tmp)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (tmp);
}
