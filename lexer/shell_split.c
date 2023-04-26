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

int	get_shell_wc(char *str, int n)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (i < n && str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i] && i < n)
			wc++;
		while (!ft_iswhitespace(str[i]) && i < n && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				i = skip_quotes(str, i, n);
			i++;
		}
	}
	return (wc);
}

char	**shell_split(char *str, int n)
{
	char	**tab;
	int		wc;
	int		i;
	int		j;

	wc = get_shell_wc(str, n);
	tab = ft_calloc(wc + 1, sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	wc = 0;
	while (i < n && str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i] && i < n)
			j = i;
		while (!ft_iswhitespace(str[i]) && i < n && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				i = skip_quotes(str, i, n);
			i++;
		}
		tab[wc] = ft_strndup(&str[j], i - j);
		if (!tab[wc])
			return (free_split(tab));
		wc++;
	}
	return (tab);
}
