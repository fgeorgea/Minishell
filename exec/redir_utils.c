/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/24 11:44:46 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_redir(t_cmd *cmd, t_pipex *p)
{
	p->infile = open_infile(cmd);
	p->outfile = open_outfile(cmd);
}