/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/14 20:09:26 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ch_env_dir(char *current_dir, char *new_dir)
{
	if (get_env_value("PWD"))
		change_env_value("PWD", new_dir);
	else
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(ft_strdup("PWD"), new_dir));
	if (get_env_value("OLDPWD"))
		change_env_value("OLDPWD", current_dir);
	else
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(ft_strdup("OLDPWD"),
			current_dir));
	}
}

static void	ft_chdir(const char *dir)
{
	char	*current_dir;
	char	*new_dir;
	
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		ft_exit(EXIT_PWD_FAILURE);
	if (chdir(dir) == -1)
	{
		print_err("cd: ", dir, ": No such file or directory\n");
		g_sh->pipe_exit = 1;
		return ;
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		ft_free(current_dir);
		ft_exit(EXIT_PWD_FAILURE);
	}
	ch_env_dir(current_dir, new_dir);
	lst_to_array(&g_sh->env);
}

void	cd_builtin(const char *str)
{
	char	*dir;

	if (str && !compare_keys(str, "~"))
	{
		ft_chdir(str);
		return ;
	}
	dir = get_env_value("HOME");
	if (!dir)
	{
		print_err("cd: ", NULL, "HOME not set\n");
		g_sh->pipe_exit = 1;
		return ;
	}
	ft_chdir(dir);
}
