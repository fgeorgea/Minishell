/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/30 15:46:39 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This will basically change the PWD and OLDPWD of the env.
static void	ch_env_dir(char *current_dir, char *new_dir)
{
	if (get_env_struct("PWD"))
		change_env_value("PWD", new_dir);
	else
		add_pwd(current_dir, new_dir);
	if (get_env_struct("OLDPWD"))
		change_env_value("OLDPWD", current_dir);
	else
		add_oldpwd(current_dir, new_dir);
}

static int	ft_chdir_2(const char *dir, char *current_dir)
{
	char	*new_dir;

	if (chdir(dir) == -1)
	{
		ft_free((void **)&current_dir);
		print_err("cd: ", (char *)dir, NSFOD, 1);
		return (0);
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		ft_free((void **)&current_dir);
		return (0);
	}
	ch_env_dir(current_dir, new_dir);
	lst_to_array(&g_sh->env);
	return (1);
}

static int	ft_chdir(const char *dir)
{
	char	*current_dir;
	char	*tmp;

	if (dir[0] == '/')
	{
		tmp = get_env_value("PWD");
		if (!tmp)
			current_dir = 0;
		else
		{
			current_dir = ft_strdup(get_env_value("PWD"));
			if (!current_dir)
				ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			return (cd_crash_handler(dir));
	}
	return (ft_chdir_2(dir, current_dir));
}

void	cd_builtin(const char *str)
{
	char	*dir;

	if (str && !compare_keys(str, "~"))
	{
		if (!ft_chdir(str))
			set_exit(1);
		return ;
	}
	dir = get_env_value("HOME");
	if (!dir)
	{
		print_err("cd: HOME not set", NULL, NULL, 1);
		return ;
	}
	if (!ft_chdir(dir))
		set_exit(1);
}
