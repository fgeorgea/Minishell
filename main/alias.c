/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:11:18 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 18:37:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_alias_to_env(char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(str, "\n");
	ft_free((void **)&str);
	if (!tmp)
		ft_exit(EXIT_MALLOC_FAILURE);
	str = ft_strdup(tmp);
	ft_free((void **)&tmp);
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
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

	fd_config = open(g_sh->config_file, O_RDONLY);
	if (fd_config == -1)
		return ;
	while (1)
	{
		str = get_next_line(fd_config);
		if (!str)
			break ;
		if (check_valid_key((const char *)str))
			add_alias_to_env(str);
	}
}
