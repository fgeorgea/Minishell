/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:00:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/29 02:21:31 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_exit_here_doc(char *str, int end_token_len, t_pipex *p)
{
	if (ft_strncmp(str, p->end_token, end_token_len) == 0)
		return (1);
	return (0);
}

void	ft_here_doc(void)
{
	t_pipex	*p;
	char	*str;
	int		end_token_len;

	p = g_sh->pipex;
	if (!p->is_heredoc)
		return ;
	end_token_len = ft_strlen(p->end_token);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
			ft_exit(EXIT_GNL_FAILURE);
		if (ft_exit_here_doc(str, end_token_len, p))
			break ;
		//ft_putstr_fd(str, p->infile);
		free(str);
	}
	free(str);
	//ft_close(&p->infile);
	//p->infile = ft_open(TMP_FILE, O_RDONLY, 0644);
}
