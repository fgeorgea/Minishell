/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:11:18 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 12:37:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_alias_to_env(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] != '=')
		return ;
	add_var_to_env((const char *)str, i);
}

void	init_aliases(void)
{
	int		fd_config;
	char	*str;
	char	*file;

	file = ft_strjoin(get_env_value("HOME"), "/.minishellrc");
	fd_config = open(file, O_RDONLY);
	if (fd_config == -1)
	{
		ft_free((void **)&file);
		return ;
	}
	while (1)
	{
		str = get_next_line(fd_config);
		if (!str)
			break ;
		if (check_valid_key((const char *)str))
			add_alias_to_env(str);
		ft_free((void **)&str);
	}
	ft_free((void **)&file);
}
