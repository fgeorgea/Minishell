/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:28:56 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 02:02:51 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(const char *custom_perror, int does_exit)
{
	t_pipex	*p;

	p = g_sh->pipex;
	ft_free_array(p->paths);
	free(p->pids);
	ft_free_void_array((void **)p->pipefd, p->nbr_pipe);
	free(g_sh->pipex);
	delete_tmp_file();
	perror(custom_perror);
	if (does_exit == -1)
		exit(EXIT_FAILURE);
}
