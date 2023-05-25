/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:14:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/17 14:16:46 by fgeorgea         ###   ########.fr       */
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
	while (i >= 0)
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

void	add_oldpwd(char *current_dir, char *new_dir)
{
	char	*old_tmp;
	t_env	*new_node;

	old_tmp = ft_strdup("OLDPWD");
	if (!old_tmp)
	{
		ft_free(current_dir);
		ft_free(new_dir);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new_node = ft_lstnew_env(old_tmp, current_dir);
	if (!new_node)
	{
		ft_free(new_dir);
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
		ft_free(current_dir);
		ft_free(new_dir);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new_node = ft_lstnew_env(old_tmp, new_dir);
	if (!new_node)
	{
		ft_free(current_dir);
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
	ft_free(dir);
	return (0);
}
