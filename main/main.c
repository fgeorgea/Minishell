/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/07 02:08:26 by fgeorgea         ###   ########.fr       */
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
		ft_readline();
		ft_add_history();
		lexer(g_sh->str);
		ft_pipex();
		set_signals(DEFAULT);
		ft_free((void **)&g_sh->str);
		ft_free((void **)&g_sh->prompt);
	}
	return (0);
}
