/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/18 19:46:26 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	init_shell(argv, env);
	if (init_signals())
		ft_exit(EXIT_SIGNAL_FAILURE);
	while (1)
	{
		g_sh->str = readline("\033[0;95mDopeorge$>\033[0;39m ");
		if (!g_sh->str)
			ft_exit(EXIT_SUCCESS);
		if (*g_sh->str)
			add_history(g_sh->str);
		lexer(g_sh->str);
		if (g_sh->cmd)
			ft_pipex();
		set_signals(DEFAULT);
		ft_free(g_sh->str);
	}
	return (0);
}
