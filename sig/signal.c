/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:56:59 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/25 20:57:44 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	catch_sigint(int sig)
{
	(void)sig;
	(void)write(1, "\n", 1);
	if (!g_sh->pipex || !g_sh->pipex->is_in_child)
	{
		g_sh->pipe_exit = 1;
		(void)rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	catch_here_sigint(int sig)
{
	(void)sig;
	restore_stdin(g_sh->pipex->dup_stdin);
	g_sh->here_doc_status = 1;
	g_sh->pipe_exit = 1;
	(void)write(1, "\n", 1);
}

void	set_signals(int state)
{
	if (state == DEFAULT)
	{
		signal(SIGINT, catch_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == SIG_HERE)
	{
		signal(SIGINT, catch_here_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == PARENT)
	{
		signal(SIGINT, catch_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}

int	init_signals(void)
{
	struct termios	term;

	set_signals(DEFAULT);
	(void)tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	(void)tcsetattr(0, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
