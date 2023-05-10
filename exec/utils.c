/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:55:29 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/11 01:06:54 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	compare_keys(char *key, char *needle)
{
	int	key_len;
	int	needle_len;

	if (!key || !needle)
		return (0);
	key_len = ft_strlen(key);
	needle_len = ft_strlen(needle);
	if ((key_len == needle_len) && ft_strncmp(key, needle, key_len) == 0)
		return (1);
	return (0);
}
