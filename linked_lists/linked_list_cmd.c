/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:22:41 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/17 23:49:18 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize_cmd(void)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = g_sh->cmd;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
    t_cmd	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast_cmd(*lst);
		last->next = new;
	}
}

t_cmd	*ft_lstnew_cmd(char **cmd, t_redir *redir)
{
    t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cmd = cmd;
	new->redir = redir;
    new->next = NULL;
	return (new);
}