/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:23:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/08 01:01:26 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_value(t_token *t, char *value, char *tmp, int *i)
{
	int	j;
	int	k;

	j = 0;
	while (j < i[1])
	{
		tmp[j] = t->word[j];
		j++;
	}
	k = 0;
	while (value && value[k])
	{
		tmp[j + k] = value[k];
		k++;
	}
	i[0] = j + k - 1;
	while (t->word[i[2]])
	{
		tmp[j + k] = t->word[i[2]];
		k++;
		i[2]++;
	}
	tmp[j + k] = 0;
}

int	insert_value(t_token *t, char *key, char *value, int *i)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(t->word)
				+ ft_strlen(value) - ft_strlen(key)));
	ft_free((void **)&key);
	if (!tmp)
	{
		if (i[4])
			ft_free((void **)&value);
		return (EXIT_MALLOC_FAILURE);
	}
	copy_value(t, value, tmp, i);
	if (i[4])
		ft_free((void **)&value);
	ft_free((void **)&t->word);
	t->word = tmp;
	return (0);
}

static char	*get_pipe_exit(int *i, char *tmp, t_list *head)
{
	char	*value;

	i[4] = 1;
	value = ft_itoa(g_sh->pipe_exit);
	if (!value)
	{
		ft_free((void **)tmp);
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (value);
}

static void	expand_var(t_token *t, int *i, t_list *head)
{
	char	*tmp;
	char	*value;

	tmp = get_var_key(t->word, i, head);
	if (tmp[0] == '?' && tmp[1] == '\0')
		value = get_pipe_exit(i, tmp, head);
	else
	{
		i[4] = 0;
		if (tmp[0] == '0')
			value = g_sh->name;
		else
			value = get_env_value(tmp);
	}
	if (insert_value(t, tmp, value, i))
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
}

/*
i[0] is main index
i[1] is index of $ being expanded
i[2] is index of character right after $key
i[3] is whether inside ""
i[4] is whether to free value
*/

void	expand(t_token *t, t_list *head)
{
	int		i[5];

	i[0] = 0;
	i[3] = 0;
	while (t->word[i[0]])
	{
		if (t->word[i[0]] == '\'' && !i[3])
			i[0] = skip_quotes(t->word, i[0]);
		if (t->word[i[0]] == '"')
		{
			if (i[3] || i[0] != skip_quotes(t->word, i[0]))
				i[3] = !i[3];
		}
		if (t->word[i[0]] == '$' && (ft_isalnum(t->word[i[0] + 1])
				|| t->word[i[0] + 1] == '_' || t->word[i[0] + 1] == '?'))
			expand_var(t, i, head);
		i[0]++;
	}
}
