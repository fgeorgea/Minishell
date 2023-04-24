/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:53:59 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/03/31 17:54:01 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	skip_quotes(char *str, int i, int max)
{
	int	j;

	j = i;
	if (str[i] == '"')
	{
		while (str[j] && (i < max || max == -1) && str[j] != '"')
			j++;
		if (str[j] == '"' && (j < max || max == -1))
			return (j);
	}
	else if (str[i] == '\'')
	{
		while (str[j] && (i < max || max == -1) && str[j] != '\'')
			j++;
		if (str[j] == '\'' && (j < max || max == -1))
			return (j);
	}
	return (i);
}

int	get_next_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = skip_quotes(str, i, -1);
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd)
	{
		if (cmd->cmd[0])
		{
			free(cmd->cmd[0])
			cmd->cmd[0] = NULL;
		}
		if (cmd->cmd[1])
		{
			free(cmd->cmd[1])
			cmd->cmd[1] = NULL;
		}
		while (cmd->redir)
		{
			if (cmd->redir->key)
				free(cmd->redir->key)
			tmp = cmd->redir->next;
			free(cmd->redir);
			cmd->redir = tmp;
		}
		free(cmd);
	}
}

