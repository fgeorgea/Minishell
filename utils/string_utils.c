/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 01:28:09 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 01:41:30 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_exit(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	dup = malloc(i + 1);
	if (!dup)
		ft_exit(EXIT_MALLOC_FAILURE);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*ft_strjoin_exit(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	while (*s2)
	{
		str[i] = *s2;
		++i;
		s2++;
	}
	str[i] = '\0';
	return (str);
}
