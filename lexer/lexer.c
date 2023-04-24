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

t_cmd	*split_cmd(char *str, int i, int j)
{
	t_cmd	*cmd;

	if (i == j)
		return (0);
	cmd = malloc(sizeof(t_cmd));
	//if (!cmd)
	//	ft_exit(EXIT_MALLOC_FAILURE);

}

void	lexer(char *str)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	if (g_sh->cmd)
		ft_free_cmd();
	i = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		j = get_next_pipe(str, i);
		if (g_sh->cmd == 0)
		{
			g_sh->cmd = split_cmd(str, i, j);
			cmd = g_sh->cmd;
		}
		else
		{
			cmd->next = split_cmd(str, i, j);
			cmd = cmd->next;
		}
		i = j;
	}
	//if (g_sh->cmd)
	//	expander(void);
}
