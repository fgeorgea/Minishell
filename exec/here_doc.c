/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:00:32 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/25 21:08:04 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_catch_kill(int sig)
{
	if (sig == SIGINT)
	{
		set_exit(1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static int	compare_endtoken(char *end_token, char *str)
{
	int	strlen;

	strlen = ft_strlen(str) - 1;
	if (strlen != (int)ft_strlen(end_token))
		return (0);
	if (ft_strncmp(str, end_token, strlen) == 0)
		return (1);
	return (0);
}

void	here_doc(char *end_token)
{
	t_pipex	*p;
	char	*str;

	set_signals(SIG_HERE);
	p = g_sh->pipex;
	p->here_doc = ft_open(p->hd_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd(end_token, 1);
		(void)write(1, "> ", 2);
		str = get_next_line(p->dup_stdin);
		if (!str)
			break ;
		if (compare_endtoken(end_token, str))
			break ;
		ft_putstr_fd(str, p->here_doc);
		ft_free((void **)&str);
	}
	ft_free((void **)&str);
	ft_close(&p->here_doc);
	set_signals(DEFAULT);
}

void	ft_here_doc_exp(char *end_token)
{
	t_pipex	*p;
	char	*str;

	set_signals(SIG_HERE);
	p = g_sh->pipex;
	p->here_doc = ft_open(p->hd_tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd(end_token, 1);
		(void)write(1, "> ", 2);
		str = get_next_line(p->dup_stdin);
		if (!str)
			break ;
		if (compare_endtoken(end_token, str))
			break ;
		expand_heredoc(&str);
		ft_putstr_fd(str, p->here_doc);
		ft_free((void **)&str);
	}
	ft_free((void **)&str);
	ft_close(&p->here_doc);
	set_signals(DEFAULT);
}
