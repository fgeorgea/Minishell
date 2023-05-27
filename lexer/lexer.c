/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:16:09 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/27 01:51:55 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_token_list(int i, t_list **head, char **arr)
{
	t_token	*tmp;
	t_list	*temp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
	{
		ft_lstclear(head, &free);
		ft_free_array(arr);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	tmp->word = arr[i];
	temp = ft_lstnew(tmp);
	if (!temp)
	{
		ft_lstclear(head, &free);
		ft_free_array(arr);
		ft_free((void **)&tmp);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	ft_lstadd_back(head, temp);
}

t_list	*pre_token(char *str)
{
	int		i;
	t_list	*head;
	char	**arr;

	arr = shell_split(str, "\040\011\012\013\014\015", 1);
	if (!arr)
		ft_exit(EXIT_MALLOC_FAILURE);
	i = 0;
	head = 0;
	while (arr[i])
	{
		create_token_list(i, &head, arr);
		i++;
	}
	ft_free((void **)&arr);
	return (head);
}

void	lexer(char *str)
{
	t_list	*words;

	ft_free_cmd();
	words = pre_token(str);
	if (!words)
		return ;
	tokenize(words);
	expander(&words, words);
	parser(words);
}
