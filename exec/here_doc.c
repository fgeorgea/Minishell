/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:00:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/04/24 17:20:06 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_exit_here_doc(char *str, int end_token_len, t_pipex *p)
{
	if (ft_strncmp(str, p->end_token, end_token_len) == 0)
		return (1);
	return (0);
}

void	ft_here_doc(t_pipex *p)
{
	char	*str;
	int		end_token_len;

	end_token_len = ft_strlen(p->end_token);
	str = get_next_line(STDIN_FILENO);
	if (!str)
		ft_error(p, "get_next_line failed to read here_doc\n", -1);
	while (*str)
	{
		if (ft_exit_here_doc(str, end_token_len, p))
			break ;
		ft_putstr_fd(str, p->infile);
		free(str);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			ft_error(p, "get_next_line failed to read here_doc\n", -1);
	}
	free(str);
	ft_close(&p->infile, p);
	p->infile = open(TMP_FILE, O_RDONLY, 0644);
	if (p->infile == -1)
		ft_error(p, "Failed to open infile\n", -1);
}
