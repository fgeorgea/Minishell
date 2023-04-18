/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/03/27 14:27:31 by dopeyrat         ###   ########.fr       */
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

/*void	ft_free_cmd(t_cmd *cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].arg)
			free(cmd[i].arg);
		if (cmd[i].redir_d)
			free(cmd[i].redir_r);
		i++;
	}
	free(cmd);
}*/

int	main(void)
{
	t_shell	*sh;

	sh = init_shell();
	if (!sh || init_signals())
		return (0);//ft_exit(sh, EXIT_FAILURE));
	while (1)
	{
		sh->str = readline("$>");
		if (!sh->str)
			exit(0);
		if (*sh->str)
			add_history(sh->str);
		//lexer(sh, sh->str);
		free(sh->str);
	}
	return (0);
}
