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

t_cmd	*get_cmd(char *str, int i, int j)
{
	t_cmd	*cmd;

	if (i == j)
	{
		syntax_error("syntax error near unexpected token `|'");
		ft_free_cmd();
		return (0);
	}
	cmd = malloc(sizeof(t_cmd));
	//if (!cmd)
	//	ft_exit(EXIT_MALLOC_FAILURE);
	cmd->cmd = 0;
	cmd->redir = 0;
	cmd->next = 0;
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

void	lexer(char *str)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	if (g_sh->cmd)
		ft_free_cmd();
	i = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (!str[i] && !g_sh->cmd)
			return ;
		else if (!str[i])
		{
			ft_free_cmd();
			syntax_error("syntax error near unexpected token `|'");
			return ;
		}
		j = get_next_pipe(str, i);
		tmp = get_cmd(str, i, j);
		if (!tmp)
			return ;
		add_cmd(tmp);
		i = j;
	}
	//expander(void);
}
