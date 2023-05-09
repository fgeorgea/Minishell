/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:00:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/09 11:38:38 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_exit_here_doc(char *str, int end_token_len, char *end_token)
{
	if (ft_strncmp(str, end_token, end_token_len) == 0)
		return (1);
	return (0);
}

void	here_doc(char *end_token)
{
	t_pipex	*p;
	char	*str;
	int		end_token_len;

	p = g_sh->pipex;
	end_token_len = ft_strlen(end_token);
	p->here_doc = ft_open(TMP_FILE, HEREDOC_FLAGS, 0644);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str)
			ft_exit(EXIT_GNL_FAILURE);
		if (ft_exit_here_doc(str, end_token_len, end_token))
			break ;
		ft_putstr_fd(str, p->here_doc);
		free(str);
	}
	free(str);
	ft_close(&p->here_doc);
}

// void	ft_here_doc_exp(char *end_token)
// {
// 	t_pipex	*p;
// 	char	*str;
// 	int		end_token_len;

// 	p = g_sh->pipex;
// 	end_token_len = ft_strlen(end_token);
// 	p->here_doc = ft_open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		str = get_next_line(STDIN_FILENO);
// 		if (!str)
// 			ft_exit(EXIT_GNL_FAILURE);
// 		//expand_heredoc(&str);
// 		if (ft_exit_here_doc(str, end_token_len, end_token))
// 			break ;
// 		ft_putstr_fd(str, p->here_doc);
// 		free(str);
// 	}
// 	free(str);
// 	ft_close(&p->here_doc);
// }