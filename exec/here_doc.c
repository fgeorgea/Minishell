/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:00:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/13 17:41:31 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_exit(EXIT_GNL_FAILURE);
		if (compare_keys(str, end_token))
			break ;
		ft_putstr_fd(str, p->here_doc);
		free(str);
	}
	free(str);
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
			ft_exit(EXIT_GNL_FAILURE);
		expand_heredoc(&str);
		if (compare_keys(str, end_token))
			break ;
		ft_putstr_fd(str, p->here_doc);
		free(str);
	}
	free(str);
	ft_close(&p->here_doc);
}
