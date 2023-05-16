/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:09:38 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/16 16:41:50 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_here_exp_var(char *str, int *i)
{
	char	*var;

	while (str[i[0]] && str[i[0]] != '"' && str[i[0]] != '\'' && !ft_iswhitespace(str[i[0]]))
		i[0]++;
	var = ft_strndup(&str[i[1] + 1], i[0] - i[1] - 1);
	if (!var)
	{
		ft_free(str);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (var);
}

char	*get_here_exp_value(char *str, int *i, char *var)
{
	char	*value;

	if (var[0] == '?' && var[1] =='\0')
	{
		i[2] = 1;
		value = ft_itoa(g_sh->pipe_exit);
		if (!value)
		{
			ft_free(str);
			ft_free(var);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		i[2] = 0;
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
	while (value[k])
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

	new = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(value) - ft_strlen(var)));
	ft_free(var);
	if (!new)
	{
		ft_free(str);
		if (i[2])
			ft_free(value);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	copy_value_here_exp(str, value, i, new);
	ft_free(str);
	if (i[2])
		ft_free(value);
	return (new);
}

void	expand_heredoc(char **str)
{
	int		i[3];
	char	*var;
	char	*value;

	i[0] = 0;
	while ((*str)[i[0]])
	{
		if ((*str)[i[0]] == '$' && (*str)[i[0] + 1] && (*str)[i[0] + 1] != '"' && (*str)[i[0] + 1] != '\'' && !ft_iswhitespace((*str)[i[0] + 1]))
		{
			i[1] = i[0];
			var = get_here_exp_var(*str, i);
			value = get_here_exp_value(*str, i, var);
			*str = insert_exp_heredoc(*str, var, value, i);
		}
		i[0]++;
	}
}
