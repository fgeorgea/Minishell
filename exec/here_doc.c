/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:00:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/16 16:39:32 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_end_heredoc(const char *str, const char *end_token)
{
	size_t	strlen;
	size_t	end_token_len;

	strlen = ft_strlen(str) - 1;
	end_token_len = ft_strlen(end_token);
	if ((strlen == end_token_len) && ft_strncmp(str, end_token, strlen) == 0)
		return (1);
	return (0);
}

void	here_doc(char *end_token)
{
	t_pipex	*p;
	char	*str;

	p = g_sh->pipex;
	p->here_doc = ft_open(TMP_FILE, HEREDOC_FLAGS, 0644);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
			ft_exit(EXIT_MALLOC_FAILURE);
		if (check_end_heredoc(str, end_token))
			break ;
		ft_putstr_fd(str, p->here_doc);
		ft_free(str);
	}
	ft_free(str);
	ft_close(&p->here_doc);
}

void	ft_here_doc_exp(char *end_token)
{
	t_pipex	*p;
	char	*str;

	p = g_sh->pipex;
	p->here_doc = ft_open(TMP_FILE, HEREDOC_FLAGS, 0644);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
			ft_exit(EXIT_MALLOC_FAILURE);
		if (check_end_heredoc(str, end_token))
			break ;
		expand_heredoc(&str);
		ft_putstr_fd(str, p->here_doc);
		ft_free(str);
	}
	ft_free(str);
	ft_close(&p->here_doc);
}
