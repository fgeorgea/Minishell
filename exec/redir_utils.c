/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:53 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/29 12:03:11 by fgeorgea         ###   ########.fr       */
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
	if (dup_stdin < 3)
		return ;
	if (close(STDIN_FILENO) == -1)
		ft_exit(EXIT_CLOSE_FAILURE);
	link_files(dup_stdin, STDIN_FILENO);
}

// Creates heredoc_tmp file name with cmd position.
void	create_hd_name(int pos)
{
	char	*base;
	char	*num;

	ft_free((void **)&g_sh->pipex->hd_tmp);
	base = "/tmp/.hd_msh_";
	num = ft_itoa(pos);
	g_sh->pipex->hd_tmp = ft_strjoin(base, num);
	ft_free((void **)&num);
	if (!g_sh->pipex->hd_tmp)
		ft_exit(EXIT_MALLOC_FAILURE);
}

// Will delete all heredoc tmp files.
void	unlink_all_tmp(void)
{
	char	*base;
	char	*num;
	char	*hd_tmp;
	size_t	i;
	size_t	nbr_cmds;

	base = "/tmp/.hd_msh_";
	i = 0;
	nbr_cmds = lstsize_cmd();
	while (i < nbr_cmds)
	{
		num = ft_itoa(i);
		hd_tmp = ft_strjoin(base, num);
		ft_free((void **)&num);
		if (hd_tmp)
			unlink((const char *)hd_tmp);
		ft_free((void **)&hd_tmp);
		i++;
	}
	ft_free((void **)&hd_tmp);
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
