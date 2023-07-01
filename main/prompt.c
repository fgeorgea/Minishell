/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 02:00:46 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/07/01 04:01:54 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	force_esc_char(char *str, int pos)
{
	g_sh->prompt->start = ft_strtrim(ft_strdup(&str[pos + 5]), "\n");
	ft_free((void **)&str);
	if (!g_sh->prompt->start)
		ft_exit(EXIT_MALLOC_FAILURE);
	str = ft_strjoin("\033", g_sh->prompt->start);
	ft_free((void **)&g_sh->prompt->start);
	if (!str)
		ft_exit(EXIT_MALLOC_FAILURE);
	g_sh->prompt->start = str;
}

static void	fetch_prompt_color(void)
{
	int		fd_config;
	char	*str;
	size_t	i;

	fd_config = open(g_sh->config_file, O_RDONLY);
	if (fd_config == -1)
		return ;
	while (1)
	{
		str = get_next_line(fd_config);
		if (!str || ft_strncmp(str, "COLOR", 5) == 0)
			break ;
		free(str);
	}
	ft_close(&fd_config);
	if (!str)
		return ;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] && str[i] != '=')
		return ;
	force_esc_char(str, i);
}

static void	get_dir_prompt(void)
{
	char	*new_dir;
	char	*tmp;

	new_dir = NULL;
	g_sh->prompt->dir = getcwd(NULL, 0);
	if (g_sh->prompt->dir)
	{
		tmp = ft_strrchr(g_sh->prompt->dir, '/');
		new_dir = ft_strdup(&tmp[1]);
		ft_free((void **)&g_sh->prompt->dir);
		g_sh->prompt->dir = new_dir;
	}
	if (!g_sh->prompt->dir)
	{
		g_sh->prompt->dir = ft_strdup("Demi-sel");
		if (!g_sh->prompt->dir)
			ft_exit(EXIT_MALLOC_FAILURE);
	}
}

static void	create_prompt_tips(void)
{
	char	*tmp;
	char	*exit_status;

	exit_status = NULL;
	if (g_sh->pipe_exit == 0 && !g_sh->prompt->start)
		g_sh->prompt->start = ft_strdup("\033[0;96m");
	if (g_sh->pipe_exit != 0)
		g_sh->prompt->start = ft_strdup("\033[0;91m");
	if (g_sh->pipe_exit == 0)
		g_sh->prompt->end = ft_strdup("$> \033[0;39m");
	else
	{
		exit_status = ft_itoa(g_sh->pipe_exit);
		tmp = ft_strjoin(" (", exit_status);
		ft_free((void **)&exit_status);
		g_sh->prompt->end = ft_strjoin(tmp, ")$> \033[0;39m");
		ft_free((void **)&tmp);
	}
}

void	create_prompt(void)
{
	char	*tmp;

	fetch_prompt_color();
	get_dir_prompt();
	create_prompt_tips();
	tmp = ft_strjoin(g_sh->prompt->start, g_sh->prompt->dir);
	g_sh->prompt->prompt = ft_strjoin(tmp, g_sh->prompt->end);
	ft_free((void **)&tmp);
	if (!g_sh->prompt->prompt)
		ft_exit(EXIT_MALLOC_FAILURE);
}
