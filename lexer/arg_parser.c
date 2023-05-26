/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:15:38 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/24 13:15:48 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_pipe_token(t_list **head)
{
	char	*str;
	t_token	*t;
	t_list	*tmp;
	int		i;

	if (*head == NULL)
		return ;
	t = (*head)->content;
	i = ft_strlen(t->word);
	if (i == 1)
	{
		tmp = (*head);
		*head = (*head)->next;
		ft_free(tmp);
		free_token(t);
		return ;
	}
	str = ft_strdup(&t->word[1]);
	if (!str)
	{
		ft_lstclear(head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	ft_free(t->word);
	t->word = str;
}

void	fill_in_arg(t_list **head, t_cmd *cmd, int n)
{
	int		i;
	t_token	*t;
	t_list	*tmp;

	i = 0;
	while (i < n)
	{
		t = (*head)->content;
		tmp = (*head);
		*head = (*head)->next;
		ft_free(tmp);
		cmd->cmd[i] = t->word;
		ft_free(t);
		i++;
	}
}

int	check_empty_cmd_redir(void)
{
	t_cmd	*cmd;

	cmd = g_sh->cmd;
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->redir == 0)
		return (1);
	return (0);
}

int	check_empty_cmd_s_err(t_list *curr, int n)
{
	if (!check_empty_cmd_redir())
		return (0);
	if (n == 0)
	{
		if (curr)
			g_sh->s_err = S_ERR_PIPE;
		else
			g_sh->s_err = S_ERR_NL;
		return (1);
	}
	if (curr && !curr->next)
	{
		g_sh->s_err = S_ERR_NL;
		return (1);
	}
	return (0);
}

void	add_cmd_arg(t_list **head, int n, t_list *curr)
{
	t_cmd	*cmd;

	if (check_empty_cmd_s_err(curr, n))
		return ;
	cmd = g_sh->cmd;
	while (cmd->next)
		cmd = cmd->next;
	cmd->cmd = ft_calloc(n + 1, sizeof(char *));
	if (!cmd->cmd)
	{
		ft_lstclear(head, &free_token);
		ft_exit(EXIT_MALLOC_FAILURE);
	}
	fill_in_arg(head, cmd, n);
	remove_pipe_token(head);
}
