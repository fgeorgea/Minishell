/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:52 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/05/14 19:30:37 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd(void)
{
	t_cmd	*tmp;
	t_redir	*temp;
	int		i;

	tmp = g_sh->cmd;
	if (!tmp)
	{
		printf("No CMD\n");
		return ;
	}
	while (tmp)
	{
		i = 1;
		printf("CMD: %s\nARG: ", tmp->cmd[0]);
		while (tmp->cmd[i])
		{
			printf("%s, ", tmp->cmd[i]);
			i++;
		}
		printf("\n");
		temp = tmp->redir;
		if (!temp)
			printf("No REDIR\n");
		else
		{
			printf("REDIR: ");
			while (temp)
			{
				if (temp->mode == OUT)
					printf("OUT ");
				else if (temp->mode == IN)
					printf("IN ");
				else if (temp->mode == OUT_APP)
					printf("OUT_APP ");
				else if (temp->mode == HEREDOC)
					printf("HEREDOC ");
				else
					printf("HEREDOC_EXP ");
				printf("%s, ", temp->key);
				temp = temp->next;
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	init_shell(argv, env);
	if (init_signals())
		ft_exit(EXIT_SIGNAL_FAILURE);
	t_env	*tmp;
	tmp = g_sh->env;
	while (tmp)
	{
		printf("%s == %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	while (1)
	{
		g_sh->str = readline("\033[0;95mDopeorge$>\033[0;39m");
		if (!g_sh->str)
			ft_exit(EXIT_SUCCESS);
		if (*g_sh->str)
			add_history(g_sh->str);
		lexer(g_sh->str);
		print_cmd();
		if (g_sh->cmd)
			ft_pipex();
		free(g_sh->str);
	}
	return (0);
}
