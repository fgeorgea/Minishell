/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/04/28 15:22:46 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd(void)
{
	t_cmd	*tmp;
	int		i;

	tmp = g_sh->cmd;
	if (!tmp)
	{
		printf("No CMD\n");
		return ;
	}
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("word: \"%s\", ", tmp->cmd[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	init_shell(argv, env);
	if (init_signals())
		ft_exit(EXIT_SIGNAL_FAILURE);
	while (1)
	{
		g_sh->str = readline("$>");
		if (!g_sh->str)
			ft_exit(EXIT_SUCCESS);
		if (*g_sh->str)
			add_history(g_sh->str);
		//lexer(g_sh->str);
		print_cmd();
		//if (g_sh->cmd)
		//	exec();
		free(g_sh->str);
	}
	return (0);
}
