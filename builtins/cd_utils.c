/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:14:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 21:02:09 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_access(char *str)
{
	int		i;
	int		j;
	char	*dir;

	dir = ft_strdup(str);
	if (!dir)
		ft_exit(EXIT_MALLOC_FAILURE);
	i = ft_strlen(dir) - 1;
	j = 0;
	ch_dir_str(dir, &i, &j);
	if (chdir(dir) != -1)
	{
		change_env_value("PWD", dir);
		ft_free((void **)&dir);
		return (1);
	}
	ft_free((void **)&dir);
	return (0);
}

char	*get_cd_special_dir(const char *str)
{
	char	*dir;

	if (!str || ft_strcmp_strict(str, "~"))
	{
		dir = get_env_value("HOME");
		if (!dir)
			print_err("cd: HOME not set", NULL, NULL, 1);
	}
	else
	{
		dir = get_env_value("OLDPWD");
		if (!dir)
			print_err("cd: OLDPWD not set", NULL, NULL, 1);
	}
	return (dir);
}
