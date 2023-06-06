/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:09:38 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/27 01:41:32 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_here_exp_var(char *str, int *i)
{
	char	*var;

	i[0]++;
	if (!ft_isdigit(str[i[0]]))
	{
		while (ft_isalnum(str[i[0]]) || str[i[0]] == '_')
			i[0]++;
	}
	if (i[1] + 1 == i[0])
		i[2] = i[0] + 1;
	else
		i[2] = i[0];
	var = ft_strndup(&str[i[1] + 1], i[2] - i[1] - 1);
	if (!var)
	{
		free(str);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (var);
}

char	*get_here_exp_value(char *str, int *i, char *var)
{
	char	*value;

	if (var[0] == '?' && var[1] == '\0')
	{
		i[3] = 1;
		value = ft_itoa(g_sh->pipe_exit);
		if (!value)
		{
			ft_free((void **)&str);
			ft_free((void **)&var);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		i[3] = 0;
		if (var[0] == '0')
			value = g_sh->name;
		else
			value = get_env_value(var);
	}
	return (value);
}

void	copy_value_here_exp(char *str, char *value, int *i, char *new)
{
	int	j;
	int	k;
	int	l;

	j = 0;
	while (j < i[1])
	{
		new[j] = str[j];
		j++;
	}
	k = 0;
	while (value && value[k])
	{
		new[j + k] = value[k];
		k++;
	}
	l = i[0];
	i[0] = j + k - 1;
	while (str[l])
	{
		new[j + k] = str[l];
		k++;
		l++;
	}
	new[j + k] = 0;
}

char	*insert_exp_heredoc(char *str, char *var, char *value, int *i)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(value) - ft_strlen(var)));
	ft_free((void **)&var);
	if (!new)
	{
		ft_free((void **)&str);
		if (i[3])
			ft_free((void **)&value);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	copy_value_here_exp(str, value, i, new);
	ft_free((void **)&str);
	if (i[3])
		ft_free((void **)&value);
	return (new);
}

void	expand_heredoc(char **str)
{
	int		i[4];
	char	*var;
	char	*value;

	i[0] = 0;
	while ((*str)[i[0]])
	{
		if ((*str)[i[0]] == '$' && (ft_isalnum((*str)[i[0] + 1])
				|| (*str)[i[0] + 1] == '_' || (*str)[i[0] + 1] == '?'))
		{
			i[1] = i[0];
			var = get_here_exp_var(*str, i);
			value = get_here_exp_value(*str, i, var);
			*str = insert_exp_heredoc(*str, var, value, i);
		}
		i[0]++;
	}
}
