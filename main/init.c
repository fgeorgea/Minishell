/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:26 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/25 20:54:40 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(void)
{
	create_prompt();
	g_sh->str = readline(g_sh->prompt->prompt);
	if (!g_sh->str)
	{
		printf("exit\n");
		ft_exit(EXIT_CTRL_D);
	}
}

void	ft_add_history(void)
{
	if (!g_sh->str || !*g_sh->str)
		return ;
	(void)add_history(g_sh->str);
}

static void	set_base_values(char **argv)
{
	g_sh = malloc(sizeof(t_shell));
	if (!g_sh)
		ft_exit(EXIT_MALLOC_FAILURE);
	g_sh->prompt = malloc(sizeof(t_prompt));
	if (!g_sh->prompt)
		ft_exit(EXIT_MALLOC_FAILURE);
	g_sh->cmd = NULL;
	g_sh->env = NULL;
	g_sh->str = NULL;
	g_sh->config_file = NULL;
	g_sh->pipex = NULL;
	g_sh->prompt->start = NULL;
	g_sh->prompt->end = NULL;
	g_sh->prompt->prompt = NULL;
	g_sh->prompt->dir = NULL;
	g_sh->name = &argv[0][2];
	g_sh->pipe_exit = 0;
}

void	init_shell(char **argv, char **env)
{
	set_base_values(argv);
	init_env(env);
	if_env_not_set();
	create_config_str();
	init_aliases();
	init_oldpwd();
	if (get_env_struct("SHLVL"))
		init_shell_lvl();
	else
		create_sh_lvl();
}
