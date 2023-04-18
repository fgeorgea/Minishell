/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeyrat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:39:53 by dpeyrat           #+#    #+#             */
/*   Updated: 2020/11/18 12:39:54 by dpeyrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static int	ft_wc(char const *str, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	if (str[0] == c)
	{
		while (str[i] == c && str[i] != 0)
			i++;
	}
	while (str[i])
	{
		wc++;
		while (str[i] != c && str[i] != 0)
			i++;
		while (str[i] == c && str[i] != 0)
			i++;
	}
	return (wc);
}

static char	**ft_set_tab(char const *str, char **tab, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != 0)
			i++;
		j = i;
		while (str[i] != c && str[i] != 0)
			i++;
		if (j != i)
		{
			tab[k] = ft_substr(str, j, i - j);
			if (!tab[k])
				return (ft_freetab(tab));
			k++;
		}
	}
	tab[k] = 0;
	return (tab);
}

static char	**ft_zero_words(char **tab)
{
	tab = malloc(sizeof(void *));
	if (!tab)
		return (0);
	tab[0] = 0;
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		wc;

	if (str == 0)
		return (0);
	tab = 0;
	wc = ft_wc(str, c);
	if (wc == 0)
		return (ft_zero_words(tab));
	tab = malloc(sizeof(void *) * (wc + 1));
	if (!tab)
		return (0);
	return (ft_set_tab(str, tab, c));
}
