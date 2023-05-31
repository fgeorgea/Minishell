/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:14:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/30 15:38:19 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_oldpwd(char *current_dir, char *new_dir)
{
	char	*old_tmp;
	t_env	*new_node;

	old_tmp = ft_strdup("OLDPWD");
	if (!old_tmp)
	{
		ft_free((void **)&current_dir);
		ft_free((void **)&new_dir);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new_node = ft_lstnew_env(old_tmp, current_dir);
	if (!new_node)
	{
		ft_free((void **)&new_dir);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	ft_lstadd_back_env(&g_sh->env, new_node);
}

void	add_pwd(char *current_dir, char *new_dir)
{
	char	*old_tmp;
	t_env	*new_node;

	old_tmp = ft_strdup("PWD");
	if (!old_tmp)
	{
		ft_free((void **)&current_dir);
		ft_free((void **)&new_dir);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new_node = ft_lstnew_env(old_tmp, new_dir);
	if (!new_node)
	{
		ft_free((void **)&current_dir);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	ft_lstadd_back_env(&g_sh->env, new_node);
}

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
		return (1);
	}
	ft_free((void **)&dir);
	return (0);
}

char	*get_cd_special_dir(const char *str)
{
	char	*dir;

	if (!str || compare_keys(str, "~"))
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
