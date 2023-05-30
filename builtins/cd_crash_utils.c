/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_crash_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/30 17:58:53 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_crash_join(const char *dir)
{
	char	*str;

	if ((dir[0] == '.' && dir[1] == '.' && !dir[2])
		|| (dir[0] == '.' && !dir[0]))
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
