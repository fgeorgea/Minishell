/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:26 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/21 20:37:32 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_env(char **env)
{
	int		i;
	int		j;
	t_env	*new_node;
	char	*key;
	char	*value;

	i = 0;
	while (env && env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		key = ft_strndup(env[i], j);
		value = ft_strdup(&env[i][j + 1]);
		if (!value)
			ft_free(key);
		new_node = ft_lstnew_env(key, value);
		if (!new_node)
			ft_exit(EXIT_MALLOC_FAILURE);
		ft_lstadd_back_env(&g_sh->env, new_node);
		i++;
	}
}

void	init_shell(char **argv, char **env)
{
	g_sh = malloc(sizeof(t_shell));
	if (!g_sh)
		ft_exit(EXIT_MALLOC_FAILURE);
	g_sh->cmd = NULL;
	g_sh->env = NULL;
	g_sh->str = NULL;
	g_sh->pipex = NULL;
	g_sh->name = &argv[0][2];
	g_sh->pipe_exit = 0;
	init_env(env);
	if_env_not_set();
	printf("%s\n", get_env_value("SHLVL"));
	init_shell_lvl();
	printf("%s\n", get_env_value("SHLVL"));
	// else
		// create_sh_lvl();
}

int	init_signals(void)
{
	struct termios	term;

	set_signals(DEFAULT);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
