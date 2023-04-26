/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/26 17:43:36 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	init_shell(argv, env);
	if (init_signals())
		ft_exit(EXIT_SIGNAL_FAILURE);
	ft_pipex(argc, argv);
	exit(0);
	while (1)
	{
		g_sh->str = readline("$>");
		if (!g_sh->str)
			ft_exit(EXIT_SUCCESS);
		if (*g_sh->str)
			add_history(g_sh->str);
		//lexer(g_sh->str);
		//if (g_sh->cmd)
		//	exec();
		free(g_sh->str);
	}
	return (0);
}
