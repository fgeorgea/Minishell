/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:40 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/16 16:15:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*finish_trim(t_token *t, int k, char *tmp)
{
	while (t->word[k + 2])
	{
		tmp[k] = t->word[k + 2];
		k++;
	}
	tmp[k] = 0;
	return (tmp);
}

static char	*get_trimmed_str(t_token *t, t_list *head, int i, int j)
{
	char	*tmp;
	int		k;

	tmp = malloc(sizeof(char) * (ft_strlen(t->word) - 1));
	if (!tmp)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	k = 0;
	while (k < i)
	{
		tmp[k] = t->word[k];
		k++;
	}
	while (k + 1 < j)
	{
		tmp[k] = t->word[k + 1];
		k++;
	}
	return (finish_trim(t, k, tmp));
}

void	trim_quotes(t_token *t, t_list *head)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (t->word[i])
	{
		if (t->word[i] == '"' || t->word[i] == '\'')
		{
			j = skip_quotes(t->word, i);
			if (i != j)
			{
				tmp = get_trimmed_str(t, head, i, j);
				ft_free(t->word);
				t->word = tmp;
				i = j - 2;
			}
		}
		i++;
	}
}
