/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:55 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/29 14:23:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_cmd(t_list *head)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		ft_lstclear(&head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
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

void	set_token_err(char *token)
{
	if (token[0] == '<' && token[1] == '<' && token[2] == '<')
		g_sh->s_err = S_ERR_TRIPLE;
	else if (token[0] == '>' && token[1] == '>')
		g_sh->s_err = S_ERR_APP;
	else if (token[0] == '<' && token[1] == '<')
		g_sh->s_err = S_ERR_HERE;
	else if (token[0] == '<' && token[1] == '>')
		g_sh->s_err = S_ERR_RW;
	else if (token[0] == '|')
		g_sh->s_err = S_ERR_PIPE;
	else if (token[0] == '<')
		g_sh->s_err = S_ERR_IN;
	else if (token[0] == '>')
		g_sh->s_err = S_ERR_OUT;
}

void	check_token_syntax(t_token *curr, t_token *next)
{
	int		i;

	i = ft_strlen(curr->word);
	if (i == 1 && (next == 0 || !next->token))
		return ;
	if (i == 2 && (curr->word[0] == curr->word[1]
			|| curr->word[1] == '|') && (next == 0 || !next->token))
		return ;
	if (i == 1)
		set_token_err(next->word);
	else if (i == 2 && curr->word[0] != curr->word[1])
		set_token_err(&curr->word[1]);
	else if (i == 2)
		set_token_err(next->word);
	else if (i > 2 && (curr->word[0] == curr->word[1] || curr->word[1] == '|'))
		set_token_err(&curr->word[2]);
	else if (i > 2)
		set_token_err(&curr->word[1]);
}

void	parse_intra_pipe(t_list **head, t_list **curr, int *i)
{
	t_token	*tmp;
	t_list	*prev;

	prev = *head;
	tmp = (*curr)->content;
	while (g_sh->s_err == NO_S_ERR && *curr
		&& !(tmp->token && *tmp->word == '|'))
	{
		if (tmp->token)
		{
			*curr = new_redir(*curr, &prev, head);
			if (*curr)
				tmp = (*curr)->content;
		}
		else
		{
			prev = *curr;
			*curr = (*curr)->next;
			if (*curr)
				tmp = (*curr)->content;
			*i = *i + 1;
		}
	}
}

void	parser(t_list *head)
{
	int		i;
	t_list	*curr;

	g_sh->s_err = NO_S_ERR;
	while (head && g_sh->s_err == NO_S_ERR)
	{
		i = 0;
		curr = head;
		new_cmd(head);
		parse_intra_pipe(&head, &curr, &i);
		if (g_sh->s_err == NO_S_ERR)
			add_cmd_arg(&head, i, curr);
	}
	if (g_sh->s_err)
	{
		ft_lstclear(&head, &free_token);
		ft_free_cmd();
		display_syntax_err();
	}
}
