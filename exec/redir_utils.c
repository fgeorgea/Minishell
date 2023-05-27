/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/27 02:30:27 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_out_redir(int redir_mode)
{
	if (redir_mode == OUT || redir_mode == OUT_APP)
		return (1);
	return (0);
}

void	restore_stdin(int dup_stdin)
{
	if (close(STDIN_FILENO) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	link_files(dup_stdin, STDIN_FILENO);
}

void	create_hd_name(int pos)
{
	char	*base;
	char	*num;

	free(g_sh->pipex->hd_tmp);
	base = "/tmp/.hd_msh_";
	num = ft_itoa(pos);
	g_sh->pipex->hd_tmp = ft_strjoin(base, num);
	free(num);
	if (!g_sh->pipex->hd_tmp)
		ft_exit(EXIT_MALLOC_FAILURE);
}

void	unlink_all_tmp(void)
{
	char	*base;
	char	*num;
	size_t	i;

	if (!g_sh->pipex)
		return ;
	base = "/tmp/.hd_msh_";
	i = 0;
	while (i < g_sh->pipex->nbr_cmds)
	{
		free(g_sh->pipex->hd_tmp);
		num = ft_itoa(i);
		g_sh->pipex->hd_tmp = ft_strjoin(base, num);
		free(num);
		if (g_sh->pipex->hd_tmp)
			unlink((const char *)g_sh->pipex->hd_tmp);
		i++;
	}
	free(g_sh->pipex->hd_tmp);
	g_sh->pipex->hd_tmp = NULL;
}

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
