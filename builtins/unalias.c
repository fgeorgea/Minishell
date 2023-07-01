/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 04:30:20 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/07/01 04:54:05 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_str_alpha(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	remove_alias_from_file(const char *str)
{
	size_t	i;
	char	**file;
	int		fd_config;
	char	*tmp;

	fd_config = ft_open(g_sh->config_file, O_RDONLY, 0644);
	if (fd_config == -1 || !is_str_alpha(str))
		return ;
	file = NULL;
	file = ft_file_to_array(g_sh->config_file, fd_config);
	fd_config = ft_open(g_sh->config_file, O_WRONLY | O_TRUNC, 0644);
	if (fd_config == -1)
		return ;
	i = 0;
	if (!file)
		return ;
	while (file[i])
	{
		tmp = ft_strdup_reject(file[i], "=");
		if (!ft_strcmp_strict(str, tmp))
			write(fd_config, file[i], ft_strlen(file[i]));
		ft_free((void **)&tmp);
		i++;
	}
	ft_close(&fd_config);
}

void	unalias_builtin(const char **arg)
{
	size_t	i;

	if (!arg || !*arg)
	{
		ft_printf(1, "please enter aliases you want to delete: alias=cmd\n");
		return ;
	}
	i = 0;
	while (arg[i])
	{
		remove_alias_from_file(arg[i]);
		i++;
	}
}
