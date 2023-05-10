/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/10 16:58:30 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_chdir(char *dir)
{
	t_env	*env;
	char	*current_dir;

	env = g_sh->env;
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		ft_exit(EXIT_PWD_FAILURE);
	if (chdir(dir) == -1)
		ft_exit(EXIT_CHDIR_FAILURE);
	change_env_value("PWD", getcwd(NULL, 0));
	change_env_value("OLDPWD", current_dir);
	lst_to_array(&g_sh->env);
}

void	ft_cd(char *str)
{
	char	*dir;

	if (!str)
	{
		dir = get_env_value("HOME", 4);
		if (!dir)
		{
			ft_putstr_fd("HOME not set\n", 2);
			return ;
		}
		ft_chdir(dir);
		return ;
	}
	ft_chdir(str);
}
