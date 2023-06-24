/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_crash_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/25 01:09:59 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ch_dir_str2(char *dir, int *i, int *j)
{
	while (*i >= 0)
	{
		if (dir[*i] == '/')
		{
			dir[*i] = '\0';
			*j = *j - 1;
			if (*j == 0)
				break ;
		}
		*i = *i - 1;
	}
}

void	ch_dir_str(char *dir, int *i, int *j)
{
	while (*i >= 0)
	{
		if (dir[*i] == '/')
		{
			if (dir[*i + 1] == '.' && dir[*i + 2] == '\0')
				dir[*i] = 0;
			else if (dir[*i + 1] == '.'
				&& dir[*i + 2] == '.' && dir[*i + 3] == '\0')
			{
				dir[*i] = 0;
				*j = *j + 1;
			}
			else
				break ;
		}
		*i = *i - 1;
	}
	ch_dir_str2(dir, i, j);
}

static char	*cd_crash_join(const char *dir)
{
	char	*str;

	if ((dir[0] == '.' && dir[1] == '.' && !dir[2])
		|| (dir[0] == '.' && !dir[1]))
	{
		if (ft_strlen(dir) == 2)
			str = ft_strjoin(get_env_value("PWD"), "/..");
		else
			str = ft_strjoin(get_env_value("PWD"), "/.");
		if (!str)
			ft_exit(EXIT_MALLOC_FAILURE);
		return (str);
	}
	str = ft_strdup(get_env_value("PWD"));
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
	return (str);
}

int	cd_crash_handler(const char *dir)
{
	char	*new_pwd;
	int		ret;

	if (!get_env_value("PWD"))
	{
		print_err(CD_RM, NULL, NULL, 1);
		return (0);
	}
	new_pwd = cd_crash_join(dir);
	change_env_value("OLDPWD", get_env_value("PWD"));
	change_env_value("PWD", new_pwd);
	ret = test_access(new_pwd);
	if (!ret)
		perror(CD_RM);
	ft_free((void **)&new_pwd);
	return (ret);
}
