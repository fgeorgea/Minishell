/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/06/16 16:34:50 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	print_welcome_message();
	init_shell(argv, env);
	if (init_signals())
		ft_exit(EXIT_SIGNAL_FAILURE);
	while (1)
	{
		ft_readline();
		ft_add_history();
		lexer(g_sh->str);
		if (g_sh->cmd)
			ft_pipex();
		set_signals(DEFAULT);
		free_readline();
	}
	return (0);
}
