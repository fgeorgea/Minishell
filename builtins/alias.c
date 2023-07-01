/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 04:07:06 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/07/01 04:26:10 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_alias(const char *str)
{
	int	config_fd;

	config_fd = open(g_sh->config_file, O_WRONLY | O_APPEND);
	if (config_fd == -1)
		return ;
	write(config_fd, "\n", 1);
	write(config_fd, str, ft_strlen(str));
	ft_close(&config_fd);
}

static int	is_valid_alias(const char *str)
{
	size_t	i;

	if (!str || !*str || !ft_strchr(str, '='))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	alias_builtin(const char **arg)
{
	size_t	i;

	if (!arg || !*arg)
	{
		ft_printf(1, "Please enter the alias name and its value: alias=value\n");
		return ;
	}
	i = 0;
	while (arg[i])
	{
		if (is_valid_alias(arg[i]))
			add_alias(arg[i]);
		else
			ft_printf(2, "`%s': bad alias\n", arg[i]);
		i++;
	}
}
