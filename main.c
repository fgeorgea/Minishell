/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/24 19:06:47 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_kill(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	init_signals(void)
{
	struct termios	term;

	if (signal(SIGINT, catch_kill) == SIG_ERR)
		return (EXIT_FAILURE);
	if (signal(SIGQUIT, catch_kill) == SIG_ERR)
		return (EXIT_FAILURE);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	return (EXIT_SUCCESS);
}

t_shell	*init_shell(void)
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (0);
	sh->cmd = NULL;
	return (sh);
}

void	ft_free_cmd(void)
{
	void	*tmp;
	int		i;

	while (g_sh->cmd)
	{
		i = 0;
		if (g_sh->cmd->cmd)
		{
			while (g_sh->cmd->cmd[i])
			{
				free(g_sh->cmd->cmd[i]);
				i++;
			}
			free(g_sh->cmd->cmd);
		}
		while (g_sh->cmd->redir)
		{
			if (g_sh->cmd->redir->key)
				free(g_sh->cmd->redir->key);
			tmp = g_sh->cmd->redir->next;
			free(g_sh->cmd->redir);
			g_sh->cmd->redir = tmp;
		}
		tmp = g_sh->cmd->next;
		free(g_sh->cmd);
		g_sh->cmd = tmp;
	}
}

int	main(void)
{
	g_sh = init_shell();
	if (!g_sh || init_signals())
		return (0);//ft_exit(sh, EXIT_FAILURE));
	while (1)
	{
		g_sh->str = readline("$>");
		if (!g_sh->str)
			exit(0);
		if (*g_sh->str)
			add_history(g_sh->str);
		//lexer(g_sh->str);
		free(g_sh->str);
	}
	return (0);
}
