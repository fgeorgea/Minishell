/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:26 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/25 13:43:29 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(char **env)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (env[0])
	{
		g_sh->env = malloc(sizeof(t_env));
		if (!g_sh->env)
			return ;
		g_sh->env->next = 0;
		i = 0;
		while (env[0][i] != '=')
			i++;
		g_sh->env->key = ft_strndup(env[0], i);
		g_sh->env->value = ft_strdup(&env[0][i + 1]);
		if (!g_sh->env->key || !g_sh->env->value)
		{
			ft_free_env();
			return ;
		}
	}
	j = 1;
	tmp = g_sh->env;
	while (env[j])
	{
		tmp->next = malloc(sizeof(t_env));
		if (!tmp->next)
		{
			ft_free_env();
			return ;
		}
		tmp = tmp->next;
		tmp->next = 0;
		i = 0;
		while (env[j][i] != '=')
			i++;
		tmp->key = ft_strndup(env[j], i);
		tmp->value = ft_strdup(&env[j][i + 1]);
		if (!tmp->key || !tmp->value)
		{
			ft_free_env();
			return ;
		}
		j++;
	}
}

void	init_shell(char **argv, char **env)
{
	g_sh = malloc(sizeof(t_shell));
	if (!g_sh)
		exit(0);
	g_sh->cmd = 0;
	g_sh->str = 0;
	g_sh->pipex = 0;
	g_sh->name = argv[0];
	init_env(env);
	if (!g_sh->env)
	{
		free(g_sh);
		exit(0);
	}
}

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
