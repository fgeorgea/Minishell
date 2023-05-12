/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:23:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/11 01:13:10 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_key(char *str, int *i, t_list *head)
{
	char	*tmp;

	i[1] = i[0];
	i[0]++;
	while (str[i[0]] != ' ' && str[i[0]] != '\''
		&& str[i[0]] && str[i[0]] != '"')
		i[0]++;
	i[2] = i[0];
	tmp = ft_strndup(&str[i[1] + 1], i[2] - i[1] - 1);
	if (!tmp)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (tmp);
}

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
	free(key);
	if (!tmp)
	{
		if (i[4])
			free(value);
		return (EXIT_MALLOC_FAILURE);
	}
	copy_value(t, value, tmp, i);
	if (i[4])
		free(value);
	free(t->word);
	t->word = tmp;
	return (0);
}

void static	expand_var(t_token *t, int *i, t_list *head)
{
	char	*tmp;
	char	*value;

	tmp = get_var_key(t->word, i, head);
	if (tmp[0] == '?' && tmp[1] == '\0')
	{
		i[4] = 1;
		value = ft_itoa(g_sh->pipe_exit);
		if (!value)
		{
			free(tmp);
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
	}
	else
	{
		i[4] = 0;
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
			i[3] = !i[3];
		if (t->word[i[0]] == '$' && t->word[i[0] + 1] != ' '
			&& t->word[i[0] + 1])
			expand_var(t, i, head);
		i[0]++;
	}
}
