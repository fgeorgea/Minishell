/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:23:31 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/02 16:28:46 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_variable(t_token *t)
{
	int	i;
	int	vc;

	i = 0;
	vc = 0;
	while (t->word[i])
	{
		if (t->word[i] == '\'')
			i = skip_quotes(t->word, i);
		if (t->word[i] == '$' && t->word[i + 1] && t->word[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var_key(char *str, int *i, t_list *head)
{
	char	*tmp;

	i[1] = i[0];
	i[0]++;
	while (str[i[0]] != ' ' && str[i[0]] != '\'' && str[i[0]] && str[i[0]] != '"')
		i[0]++;
	i[2] = i[0];
	tmp = ft_strndup(&str[i[1] + 1], i[2] - i[1] - 1);
	if (!tmp)
	{
		ft_lstclear(&head, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (tmp);
}

int	insert_value(t_token *t, char *key, char *value, int *i)
{
	char	*tmp;
	int		j;
	int		k;

	tmp = malloc(sizeof(char) * (ft_strlen(t->word) + ft_strlen(value) - ft_strlen(key)));
	free(key);
	if (!tmp)
	{
		if (i[4])
			free(value);
		return (EXIT_MALLOC_FAILURE);
	}
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
	if (i[4])
		free(value);
	free(t->word);
	t->word = tmp;
	return (0);
}

/*
i[0] is main index, i[1] is index of $ being expanded,
i[2] is index of character right after $key, i[3] is whether inside ",
i[4] is whether to free value
*/

void	expand(t_token *t, t_list *head)
{
	char	*tmp;
	int		i[5];
	char	*value;

	i[0] = 0;
	i[3] = 0;
	while (t->word[i[0]])
	{
		if (t->word[i[0]] == '\'' && !i[3])
			i[0] = skip_quotes(t->word, i[0]);
		if (t->word[i[0]] == '"')
			i[3] = !i[3];
		if (t->word[i[0]] == '$' && t->word[i[0] + 1] != ' ' && t->word[i[0] + 1])
		{
			tmp = get_var_key(t->word, i, head);
			if (tmp[0] == '?' && tmp[1] == '\0')
			{
				i[4] = 1;
				value = ft_itoa(g_sh->pipe_exit);
				if (!value)
				{
					free(tmp);
					ft_lstclear(&head, &free);
					ft_exit(EXIT_MALLOC_FAILURE);
				}
			}
			else
			{
				i[4] = 0;
				value = get_env_value(tmp, ft_strlen(tmp));
			}
			if (insert_value(t, tmp, value, i))
			{
				ft_lstclear(&head, &free);
				ft_exit(EXIT_MALLOC_FAILURE);
			}
		}
		i[0]++;
	}
}

void	expander(t_list *head)
{
	t_list	*curr;
	t_token	*tmp;

	curr = head;
	while (curr)
	{
		tmp = curr->content;
		if (has_variable(tmp))
			expand(tmp, head);
		curr = curr->next;
	}
}