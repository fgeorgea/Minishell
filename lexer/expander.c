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
	tmp = ft_strndup(&str[i[1]], i[2] - i[1]);
	if (!tmp)
	{
		ft_lstclear(&head, &free);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (tmp);
}

void	expand(t_token *t, t_list *head)
{
	char	*tmp;
	int		i[4];
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
				value = ft_itoa(g_sh->exit);
			} 
			value = get_env_value(tmp, ft_strlen(tmp));
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
		else
			curr = curr->next;
	}
}