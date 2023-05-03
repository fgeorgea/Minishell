/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:16:09 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/02 16:30:57 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (g_sh->cmd == 0)
		g_sh->cmd = cmd;
	else
	{
		tmp = g_sh->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}

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
			ft_lstclear(&head, &free);
			ft_free_array(arr);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		tmp->word = arr[i];
		temp = ft_lstnew(tmp);
		if (!temp)
		{
			ft_lstclear(&head, &free);
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
	t_token	*tmp;

	ft_free_cmd();
	words = pre_token(str);
	if (!words)
		return ;
	tokenize(words);
	expander(words);
	post_expander(words);
	while (words)
	{
		tmp = words->content;
		printf("%s -> token %d\n", tmp->word, tmp->token);
		words = words->next;
	}
}
