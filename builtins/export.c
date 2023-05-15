/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:54:57 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/16 01:33:44 by fgeorgea         ###   ########.fr       */
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

	key = ft_substr(str, 0, pos - 1);
	if (!key)
		ft_exit(EXIT_MALLOC_FAILURE);
	value = ft_strdup(&str[pos + 1]);
	if (!value)
	{
		ft_free(key);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	env = get_env_struct(key);
	if (env && (env->value || !env->value))
		join_values_app(key, env->value, value);
	else
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
		return ;
	}
	ft_free(key);
	ft_free(value);
}

static void	add_var_to_env(const char *str, size_t pos)
{
	t_env	*env;
	char	*key;
	char	*value;

	key = ft_substr(str, 0, pos);
	if (!key)
		ft_exit(EXIT_MALLOC_FAILURE);
	value = ft_strdup(&str[pos + 1]);
	if (!value)
	{
		ft_free(key);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	env = get_env_struct(key);
	if (env)
		change_env_value(key, value);
	else
	{
		ft_lstadd_back_env(&g_sh->env, ft_lstnew_env(key, value));
		return ;
	}
	ft_free(key);
	ft_free(value);
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
			print_err("export: `", strs[i], "': not a valid identifier\n");
			g_sh->pipe_exit = 1;
		}
		i++;
	}
	lst_to_array(&g_sh->env);
}
