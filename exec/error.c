/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:28:56 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:10:45 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_pipex *p, const char *custom_perror, int does_exit)
{
	ft_free_array(p->paths);
	free(p->pids);
	ft_free_int_array(p->pipefd, p->nbr_pipe);
	ft_lstclear_pipex(&p->lst);
	ft_unlink_tmp();
	ft_putstr_fd("Error\n", 2);
	perror(custom_perror);
	if (does_exit == -1)
		exit(EXIT_FAILURE);
}
