/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:45:39 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/23 15:45:48 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_token_wc(char *str, char *sep)
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

static char	*sub_word_spt(char *str, char *sep, int *i)
{
	int		s;
	int		j;

	s = is_in_sep(str[*i], sep);
	j = *i;
	while (str[*i] && s == is_in_sep(str[*i], sep))
		*i = *i + 1;
	return (ft_strndup(&str[j], (*i) - j));
}

char	**shell_split_token(char *str, char *sep)
{
	char	**arr;
	int		wc;
	int		i;

	wc = get_token_wc(str, sep);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (0);
	i = 0;
	wc = 0;
	while (str[i])
	{
		arr[wc] = sub_word_spt(str, sep, &i);
		if (!arr[wc])
			return (free_split(arr));
		wc++;
	}
	arr[wc] = 0;
	return (arr);
}
