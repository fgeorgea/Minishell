/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/04 14:35:25 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_chdir(char *dir)
{
	t_env	*env;
	char	*oldpwd;
	char	*oldtmp;

	env = g_sh->env;
	oldpwd = ft_pwd();
	oldtmp = get_env_value("OLDPWD", 6);
	if (!oldtmp)
	{
		if (!chdir(dir))
			ft_exit(EXIT_CHDIR_FAILURE);
		return ;
	}
	free(oldtmp);
	env->value = oldpwd;
	if (!chdir(dir))
		ft_exit(EXIT_CHDIR_FAILURE);
	ft_free_array(g_sh->pipex->env_array);
	g_sh->pipex->env_array = lst_to_array(&g_sh->env);
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
