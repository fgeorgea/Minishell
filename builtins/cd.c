/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 16:48:44 by fgeorgea         ###   ########.fr       */
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
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd((char *)dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return ;
	}
	ft_chdir(dir);
}
