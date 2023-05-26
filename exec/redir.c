/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:38:24 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/26 15:10:40 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_redir_open(char *file, int mode, int perm)
{
	int	fd;

	fd = ft_open_redir(file, mode, perm);
	if (fd == -1)
	{
		print_perror(file, ": ", 1);
		return (0);
	}
	ft_close(&fd);
	return (1);
}

void	setup_redir(t_redir *redirection, t_pipex *p)
{
	t_redir	*redir;
	t_redir *last_in;
	t_redir	*last_out;
			
	if (!redirection)
		return ;
	redir = redirection;
	last_in = NULL;
	last_out = NULL;
	while (redir)
	{
		if (!test_redir_open(redir->key, redir->mode, 0644))
		{
			if (is_out_redir(redir->mode))
				p->outfile = -1;
			else
				p->infile = -1;
			break ;
		}
		if (is_out_redir(redir->mode))
			last_out = redir;
		else
			last_in = redir;
		redir = redir->next;
	}
	if (last_in)
		p->infile = ft_open_redir(last_in->key, last_in->mode, 0644);
	if (last_out)
		p->outfile = ft_open_redir(last_out->key, last_out->mode, 0644);
}
