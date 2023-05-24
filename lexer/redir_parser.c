/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:11:59 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/24 13:12:08 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir_mode(t_token *token, t_token *next)
{
	if (token->word[0] == '>' && token->word[1] == '>')
		return (OUT_APP);
	if (token->word[0] == '<' && token->word[1] == '<' && next->quotes)
		return (HEREDOC);
	if (token->word[0] == '<' && token->word[1] == '<')
		return (HEREDOC_EXP);
	if (token->word[0] == '>')
		return (OUT);
	return (IN);
}

void	add_redir(t_redir *new, t_list **head, t_list *curr, t_token *content)
{
	t_cmd	*tmp;
	t_redir	*temp;

	if (!new)
	{
		ft_lstclear(head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new->mode = get_redir_mode(curr->content, curr->next->content);
	new->key = content->word;
	tmp = g_sh->cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->redir == 0)
		tmp->redir = new;
	else
	{
		temp = tmp->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_list	*remove_redir_list(t_list *curr, t_list **head, t_list **prev)
{
	t_list	*ret;

	if (curr == *prev)
	{
		*head = curr->next->next;
		*prev = *head;
		ret = *head;
	}
	else
	{
		(*prev)->next = curr->next->next;
		ret = (*prev)->next;
	}
	ft_free(curr->next->content);
	ft_free(curr->next);
	free_token(curr->content);
	ft_free(curr);
	return (ret);
}

t_list	*new_redir(t_list *curr, t_list **prev, t_list **head)
{
	t_token	*content;

	if (!curr->next)
	{
		g_sh->s_err = S_ERR_NL;
		content = 0;
	}
	else
		content = curr->next->content;
	check_token_syntax(curr->content, content);
	if (g_sh->s_err)
		return (curr);
	add_redir(ft_calloc(1, sizeof(t_redir)), head, curr, content);
	return (remove_redir_list(curr, head, prev));
}
