/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:22:41 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/26 11:41:26 by fgeorgea         ###   ########.fr       */
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
