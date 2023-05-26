/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/26 14:38:33 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	setup_redir(t_cmd *cmd, t_pipex *p)
// {
// 	p->infile = open_infile(cmd);
// 	if (p->infile >= 0)
// 		p->outfile = open_outfile(cmd);
// 	else
// 		p->outfile = 0;
// }

int	is_out_redir(int redir_mode)
{
	if (redir_mode == OUT || redir_mode == OUT_APP)
		return (1);
	return (0);
}
