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

static char	**get_shell_wc(char *str, char *sep, int s)
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
			if (s && (str[i] == '"' || str[i] == '\''))
				i = skip_quotes(str, i);
			i++;
		}
		while (is_in_sep(str[i], sep))
			i++;
	}
	return (malloc(sizeof(char *) * (wc + 1)));
}

static int	get_next_sep(char *str, char *sep, int s, int i)
{
	while (!is_in_sep(str[i], sep) && str[i])
	{
		if (s && (str[i] == '"' || str[i] == '\''))
			i = skip_quotes(str, i);
		i++;
	}
	return (i);
}

char	**shell_split(char *str, char *sep, int s)
{
	char	**tab;
	int		wc;
	int		j;
	int		i;

	tab = get_shell_wc(str, sep, s);
	if (!tab)
		return (0);
	wc = 0;
	i = 0;
	while (str[i])
	{
		while (is_in_sep(str[i], sep))
			i++;
		if (!str[i])
			break ;
		j = i;
		i = get_next_sep(str, sep, s, i);
		tab[wc] = ft_strndup(&str[j], i - j);
		if (!tab[wc])
			return (free_split(tab));
		wc++;
	}
	tab[wc] = 0;
	return (tab);
}
