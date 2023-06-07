/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:43:26 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/07 02:08:07 by fgeorgea         ###   ########.fr       */
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
			ft_free((void **)&key);
		new_node = ft_lstnew_env(key, value);
		if (!new_node)
			ft_exit(EXIT_MALLOC_FAILURE);
		ft_lstadd_back_env(&g_sh->env, new_node);
		i++;
	}
}

void static	init_oldpwd(void)
{
	t_env	*oldpwd;

	oldpwd = get_env_struct("OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = NULL;
	}
	else
	{
		oldpwd = ft_calloc(1, sizeof(t_env));
		if (!oldpwd)
			ft_exit(EXIT_MALLOC_FAILURE);
		oldpwd->key = ft_strdup("OLDPWD");
		ft_lstadd_back_env(&g_sh->env, oldpwd);
		if (!oldpwd->key)
			ft_exit(EXIT_MALLOC_FAILURE);
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
	g_sh->prompt = NULL;
	g_sh->pipex = NULL;
	g_sh->name = &argv[0][2];
	g_sh->pipe_exit = 0;
	init_env(env);
	if_env_not_set();
	init_oldpwd();
	if (get_env_struct("SHLVL"))
		init_shell_lvl();
	else
		create_sh_lvl();
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
