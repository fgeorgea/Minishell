/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:16:09 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/04 19:40:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*pre_token(char *str)
{
	int		i;
	t_token	*tmp;
	t_list	*temp;
	t_list	*head;
	char	**arr;

	if (g_sh->cmd)
		ft_free_cmd();
	arr = shell_split(str, "\040\011\012\013\014\015");
	if (!arr)
		ft_exit(EXIT_MALLOC_FAILURE);
	i = 0;
	head = 0;
	while (arr[i])
	{
		tmp = malloc(sizeof(t_token));
		if (!tmp)
		{
			ft_lstclear(&head, &free_token);
			ft_free_array(arr);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		tmp->word = arr[i];
		tmp->pre_exp = 0;
		temp = ft_lstnew(tmp);
		if (!temp)
		{
			ft_lstclear(&head, &free_token);
			ft_free_array(arr);
			free(tmp);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		ft_lstadd_back(&head, temp);
		i++;
	}
	free(arr);
	return (head);
}

/*
Split into words -> pre_token
tokenization -> tokenize
expander -> expander
split into words -> post_token
remove quotes
*/

void	lexer(char *str)
{
	t_list	*words;

	ft_free_cmd();
	words = pre_token(str);
	if (!words)
		return ;
	tokenize(words);
	expander(words);
	post_expander(words);
	t_token	*t;
	t_list	*tmp;
	tmp = words;
	while (tmp)
	{
		t = tmp->content;
		printf("%s\n", t->word);
		tmp = tmp->next;
	}
	remove_quotes(words);
	parser(words);
}
