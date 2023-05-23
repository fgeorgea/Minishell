/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/23 18:21:17 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_redir(t_cmd *cmd, t_pipex *p)
{
	p->infile = open_infile(cmd);
	if (p->infile < 0)
		return (0);
	if (g_sh->here_doc_status)
		return (0);
	p->outfile = open_outfile(cmd);
	if (p->outfile < 0)
		return (0);
	return (1);
}