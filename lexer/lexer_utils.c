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

#include "../minishell.h"

int	skip_quotes(char *str, int i)
{
	int	j;

	j = i + 1;
	if (str[i] == '"')
	{
		while (str[j] && str[j] != '"')
			j++;
		if (str[j] == '"')
			return (j);
	}
	else if (str[i] == '\'')
	{
		while (str[j] && str[j] != '\'')
			j++;
		if (str[j] == '\'')
			return (j);
	}
	return (i);
}

int	get_next_pipe(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i);
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (i);
}
