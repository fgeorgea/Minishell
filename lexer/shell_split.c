/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:15:08 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/26 13:15:21 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**free_split(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}

int	get_shell_wc(char *str, char *sep)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
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
		while (is_in_sep(str[i], sep))
			i++;
	}
	return (wc);
}

char	**shell_split(char *str, char *sep)
{
	char	**tab;
	int		wc;
	int		i;
	int		j;

	wc = get_shell_wc(str, sep);
	tab = malloc((wc + 1) * sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	wc = 0;
	while (str[i])
	{
		while (is_in_sep(str[i], sep))
			i++;
		if (str[i])
			j = i;
		while (!is_in_sep(str[i], sep) && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				i = skip_quotes(str, i);
			i++;
		}
		tab[wc] = ft_strndup(&str[j], i - j);
		if (!tab[wc])
			return (free_split(tab));
		wc++;
		while (is_in_sep(str[i], sep))
			i++;
	}
	tab[wc] = 0;
	return (tab);
}
