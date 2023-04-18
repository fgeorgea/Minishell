/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:53:59 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/03/31 17:54:01 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	skip_quotes(char *str, int i, int max)
{
	int	j;

	j = i;
	if (str[i] == '"')
	{
		while (str[j] && (i < max || max == -1) && str[j] != '"')
			j++;
		if (str[j] == '"' && (j < max || max == -1))
			return (j);
	}
	else if (str[i] == '\'')
	{
		while (str[j] && (i < max || max == -1) && str[j] != '\'')
			j++;
		if (str[j] == '\'' && (j < max || max == -1))
			return (j);
	}
	return (i);
}

int	count_cmds(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i, -1);
		if (str[i] == '|')
			c++;
		i++;
	}
	return (c);
}

int	get_next_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i, -1);
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

int	count_redir(char *str, int n)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < n)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i, -1);
		if (str[i] == '>')
		{
			c++;
			if (str[i + 1] == '>')
				i++;
		}
		else if (str[i] == '<')
		{
			c++;
			if (str[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (c);
}

