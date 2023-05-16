/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:32:17 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/16 18:41:12 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ch_env_dir(char *current_dir, char *new_dir)
{
	if (get_env_value("PWD"))
		change_env_value("PWD", new_dir);
	else
	{
		ft_lstadd_back_env(&g_sh->env,
			ft_lstnew_env(ft_strdup("PWD"), new_dir));
	}
	if (get_env_struct("OLDPWD"))
		change_env_value("OLDPWD", current_dir);
	else
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(ft_strdup("OLDPWD"),
				current_dir));
	}
	ft_free(current_dir);
	ft_free(new_dir);
}

static int	test_access(char *str)
{
	int		i;
	int		j;
	char	*dir;

	dir = ft_strdup(str);
	i = ft_strlen(dir) - 1;
	j = 0;
	while (i >= 0)
	{
		if (dir[i] == '/')
		{
			if (dir[i + 1] == '.' && dir[i + 2] == '\0')
				dir[i] = 0;
			else if (dir[i + 1] == '.' && dir[i + 2] == '.' && dir[i + 3] == '\0')
			{
				dir[i] = 0;
				j++;
			}
			else
				break ;
		}
		i--;
	}
	while (i >= 0)
	{
		if (dir[i] == '/')
		{
			dir[i] = '\0';
			j--;
			if (j == 0)
				break ;
		}
		i--;
	}
	if (chdir(dir) != - 1)
	{
		change_env_value("PWD", dir);
		return (1);
	}
	free(dir);
	return (0);
}

static int	cd_crash_handler(const char *dir)
{
	char	*tmp;
	char	*new_pwd;
	int		ret;

	tmp = NULL;
	new_pwd = NULL;
	if (!get_env_value("PWD"))
		return (0);
	tmp = ft_strjoin(get_env_value("PWD"), "/");
	if (!tmp)
		ft_exit(EXIT_MALLOC_FAILURE);
	new_pwd = ft_strjoin(tmp, dir);
	if (!new_pwd)
	{
		ft_free(tmp);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	ft_free(tmp);
	change_env_value("OLDPWD", get_env_value("PWD"));
	change_env_value("PWD", new_pwd);
	ret = test_access(new_pwd);
	if (!ret)
		perror(CD_RM);
	printf("%d\n", ret);
	return (ret);
}

static int	ft_chdir(const char *dir)
{
	char	*current_dir;
	char	*new_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (cd_crash_handler(dir));
	if (chdir(dir) == -1)
	{
		ft_free(current_dir);
		print_err("cd: ", dir, ": No such file or directory\n");
		return (0);
	}
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		ft_free(current_dir);
		return (0);
	}
	ch_env_dir(current_dir, new_dir);
	lst_to_array(&g_sh->env);
	return (1);
}

void	cd_builtin(const char *str)
{
	char	*dir;

	if (str && !compare_keys(str, "~"))
	{
		if (!ft_chdir(str))
			g_sh->pipe_exit = 1;
		return ;
	}
	dir = get_env_value("HOME");
	if (!dir)
	{
		print_err("cd: ", NULL, "HOME not set\n");
		g_sh->pipe_exit = 1;
		return ;
	}
	if (!ft_chdir(dir))
		g_sh->pipe_exit = 1;
}
