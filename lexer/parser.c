/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:55 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/03 15:15:07 by dopeyrat         ###   ########.fr       */
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

int	get_redir_mode(t_list *curr)
{

}

t_list	*add_redir(t_token *t, t_list *prev, t_list **head, t_cmd *cmd)
{
	t_token	*tmp;
	t_list	*curr;
	int		mode;

	tmp = prev->content;
	if (prev == *head && tmp->token)
		curr = prev;
	else
		curr = prev->next;
	mode = get_redir_mode(curr);
}

void	parser(t_list *head)
{
	t_token	*tmp;
	t_list	*curr;
	t_list	*prev;
	t_cmd	*cmd;
	int		i;

	g_sh->s_err = 0;
	curr = head;
	prev = head;
	while (curr && !g_sh->s_err)
	{
		i = 0;
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		tmp = curr->content;
		while (!tmp->token && *tmp->word != '|' && !g_sh->s_err)
		{
			if (tmp->token)
				curr = add_redir(tmp, prev, &head, cmd);
			else
			{
				prev = curr;
				curr = curr->next;
				tmp = curr->content;
				i++;
			}
		}
	}
}