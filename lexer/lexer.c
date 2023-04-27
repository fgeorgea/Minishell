/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:16:09 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/03/31 15:16:11 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*get_cmd(char *str)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->next = 0;
	cmd->redir = 0;
	cmd->cmd = shell_split(str, "\040\011\012\013\014\015");
	if (!cmd->cmd)
	{
		free(cmd);
		return (0);
	}
	return (cmd);
}

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

/*
Split into words -> tokenization -> expander -> split into words -> quotes
*/

void	lexer(char *str)
{
	int		i;
	int		m_fail;
	t_cmd	*tmp;
	char	**arr;

	if (g_sh->cmd)
		ft_free_cmd();
	arr = shell_split(str, "|");
	if (!arr)
		ft_exit(EXIT_MALLOC_FAILURE);
	i = 0;
	m_fail = 0;
	while (arr[i])
	{
		if (!m_fail)
		{
			tmp = get_cmd(arr[i]);
			if (!tmp)
				m_fail = 1;
			else
				add_cmd(tmp);
		}
		free(arr[i]);
		i++;
	}
	free(arr);
	if (m_fail)
		ft_exit(EXIT_MALLOC_FAILURE);
	//expander(void);
}
