/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:54:57 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 18:28:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_export(const char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[len] && (str[len] != '=' && str[len] != '+'))
		len++;
	if (!str[len] || (str[len] == '+' && str[len + 1] != '='))
		return (0);
	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	add_var_to_env_app(const char *str, size_t pos)
{
	t_env	*env;
	char	*key;
	char	*value;
	char	*old_value;

	key = ft_substr(str, 0, pos - 1);
	value = ft_strdup(&str[pos + 1]);
	env = get_env_struct(key);
	if (!env)
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
		return ;
	}
	if (!env->value)
		env->value = value;
	else
	{
		old_value = ft_strdup(env->value);
		ft_free(env->value);
		env->value = ft_strjoin(old_value, value);
	}
	ft_free(key);
}

static void	add_var_to_env(const char *str, size_t pos)
{
	t_env	*env;
	char	*key;
	char	*value;

	key = ft_substr(str, 0, pos);
	value = ft_strdup(&str[pos + 1]);
	env = get_env_struct(key);
	if (!env)
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
		return ;
	}
	change_env_value(key, value);
}

static void	check_append(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		add_var_to_env_app(str, i);
	else
		add_var_to_env(str, i);
}

void	export_builtin(const char **strs)
{
	size_t	i;

	if (!*strs)
	{
		sort_env_ascii();
		print_export();
		return ;
	}
	i = 0;
	while (strs[i])
	{
		if (check_valid_export(strs[i]))
			check_append(strs[i]);
		else
		{
			ft_printf_fd(2, "Minishell: export: '%s': not a valid identifier\n",
			strs[i]);
			g_sh->pipe_exit = 1;
		}
		i++;
	}
	lst_to_array(&g_sh->env);
}
