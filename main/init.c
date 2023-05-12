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

	if (!env)
	{
		g_sh->env = 0;
		return ;
	}
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

void	init_shell_lvl(void)
{
	t_env	*tmp;
	int		v;

	tmp = g_sh->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "SHLVL", 6) == 0)
		{
			printf("%s\n", tmp->value);
			v = ft_atoi(tmp->value);
			printf("%d\n", v);
			free(tmp->value);
			if (v < 0 || v >= 1000)
				tmp->value = ft_strdup("0");
			else if (v == 999)
				tmp->value = ft_strdup("");
			else
				tmp->value = ft_itoa(v + 1);
			if (!tmp->value)
				ft_exit(EXIT_MALLOC_FAILURE);
			return ;
		}
		tmp = tmp->next;
	}
	if (g_sh->env)
	{
		tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
	}
	else
	{
		g_sh->env = malloc(sizeof(t_env));
		tmp = g_sh->env;
	}
	if (!tmp)
		ft_exit(EXIT_MALLOC_FAILURE);
	tmp->key = ft_strdup("SHLVL");
	tmp->value = ft_strdup("1");
	tmp->next = 0;
	if (!tmp->key || !tmp->value)
		ft_exit(EXIT_MALLOC_FAILURE);
}

void	init_shell(char **argv, char **env)
{
	g_sh = malloc(sizeof(t_shell));
	if (!g_sh)
		ft_exit(EXIT_MALLOC_FAILURE);
	g_sh->cmd = 0;
	g_sh->str = 0;
	g_sh->pipex = 0;
	g_sh->name = argv[0];
	g_sh->pipe_exit = 0;
	init_env(env);
	init_shell_lvl();
	if (!g_sh->env)
		ft_exit(EXIT_MALLOC_FAILURE);
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
