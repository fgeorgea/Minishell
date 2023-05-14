/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/14 16:19:20 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_chdir(const char *dir)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		ft_exit(EXIT_PWD_FAILURE);
	if (chdir(dir) == -1)
	{
		print_err("cd: ", dir, ": No such file or directory\n");
		g_sh->pipe_exit = 1;
		return ;
	}
	change_env_value("PWD", getcwd(NULL, 0));
	change_env_value("OLDPWD", current_dir);
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
