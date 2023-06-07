/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 02:00:46 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/07 11:45:05 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_history(void)
{
	if (*g_sh->str)
		add_history(g_sh->str);
}

static char	*get_dir_prompt(void)
{
	char	*dir;
	char	*new_dir;
	char	*tmp;

	new_dir = NULL;
	dir = getcwd(NULL, 0);
	if (dir)
	{
		tmp = ft_strrchr(dir, '/');
		new_dir = ft_strdup(&tmp[1]);
		ft_free((void **)&dir);
		dir = new_dir;
	}
	if (!dir)
	{
		dir = ft_strdup("Demi-sel");
		if (!dir)
			ft_exit(EXIT_MALLOC_FAILURE);
	}
	return (dir);
}

static void	create_prompt_tips(char **start, char **end)
{
	char	*tmp;

	if (g_sh->pipe_exit == 0)
		*start = ft_strdup("\033[0;96m");
	else
		*start = ft_strdup("\033[0;91m");
	if (g_sh->pipe_exit == 0)
		*end = ft_strdup("$> \033[0;39m");
	else
	{
		tmp = ft_strjoin(" (", ft_itoa(g_sh->pipe_exit));
		*end = ft_strjoin(tmp, ")$> \033[0;39m");
		ft_free((void **)&tmp);
	}
}

static char	*create_prompt(char *dir)
{
	char	*end;
	char	*start;
	char	*prompt;
	char	*tmp;

	create_prompt_tips(&start, &end);
	tmp = ft_strjoin(start, dir);
	prompt = ft_strjoin(tmp, end);
	ft_free((void **)&start);
	ft_free((void **)&end);
	ft_free((void **)&dir);
	ft_free((void **)&tmp);
	if (!prompt)
		ft_exit(EXIT_MALLOC_FAILURE);
	return (prompt);
}

void	ft_readline(void)
{
	char	*dir;

	dir = get_dir_prompt();
	g_sh->prompt = create_prompt(dir);
	g_sh->str = readline(g_sh->prompt);
	if (!g_sh->str)
	{
		printf("exit\n");
		ft_exit(EXIT_CTRL_D);
	}
}
