/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:55 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/04 19:46:34 by fgeorgea         ###   ########.fr       */
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

void	add_redir(t_redir *redir)
{
	t_cmd	*tmp;
	t_redir	*temp;

	tmp = g_sh->cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->redir == 0)
		tmp->redir = redir;
	else
	{
		temp = tmp->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = redir;
	}
}

void	set_token_err(char *token)
{
	if (token[0] == '>' && token[1] == '>')
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
	if (i == 2 && (curr->word[0] == curr->word[1] || curr->word[1] == '|') && (next == 0 || !next->token))
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

t_list	*new_redir(t_list *curr, t_list **prev, t_list **head)
{
	t_token	*content;
	t_redir	*new;
	t_list	*ret;

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
	new = malloc(sizeof(t_redir));
	if (!new)
	{
		ft_lstclear(head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	new->next = 0;
	new->mode = get_redir_mode(curr->content, curr->next->content);
	new->key = content->word;
	add_redir(new);
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
	free(curr->next->content);
	free(curr->next);
	free_token(curr->content);
	free(curr);
	return (ret);
}

void	add_cmd_arg(t_list **head, int n, t_list *curr, t_cmd *cmd)
{
	int		i;
	t_token	*t;
	t_list	*tmp;
	char	*str;

	if (n == 0)
	{
		if (curr)
			g_sh->s_err = S_ERR_PIPE;
		else
			g_sh->s_err = S_ERR_NL;
		return ;
	}
	cmd->cmd = ft_calloc(n + 1, sizeof(char *));
	if (!cmd->cmd)
	{
		ft_lstclear(head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	i = 0;
	while (i < n)
	{
		t = (*head)->content;
		tmp = (*head);
		*head = (*head)->next;
		free(tmp);
		cmd->cmd[i] = t->word;
		free(t);
		i++;
	}
	if (*head == NULL)
		return ;
	t = (*head)->content;
	i = ft_strlen(t->word);
	if (i == 1)
	{
		tmp = (*head);
		*head = (*head)->next;
		free(tmp);
		free_token(t);
		return ;
	}
	str = ft_strdup(&t->word[1]);
	if (!str)
	{
		ft_lstclear(head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	free(t->word);
	t->word = str;
}

void	parser(t_list *head)
{
	t_token	*tmp;
	t_list	*curr;
	t_list	*prev;
	t_cmd	*cmd;
	int		i;

	g_sh->s_err = NO_S_ERR;
	while (head && g_sh->s_err == NO_S_ERR)
	{
		curr = head;
		prev = head;
		i = 0;
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			ft_lstclear(&head, &free_token);
			ft_exit(EXIT_MALLOC_FAILURE);
		}
		add_cmd(cmd);
		tmp = curr->content;
		while (g_sh->s_err == NO_S_ERR && curr && !(tmp->token && *tmp->word == '|'))
		{
			if (tmp->token)
			{
				curr = new_redir(curr, &prev, &head);
				if (curr)
					tmp = curr->content;
			}
			else
			{
				prev = curr;
				curr = curr->next;
				if (curr)
					tmp = curr->content;
				i++;
			}
		}
		if (g_sh->s_err == NO_S_ERR)
			add_cmd_arg(&head, i, curr, cmd);
	}
	if (g_sh->s_err)
	{
		ft_lstclear(&head, &free_token);
		ft_free_cmd();
		display_syntax_err();
	}
}
