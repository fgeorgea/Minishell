/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:17:30 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/19 01:36:21 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Will print the current directory.
	In case getcwd crashes, it will try to print the PWD env var.
*/
void	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		return ;
	}
	pwd = get_env_value("PWD");
	if (!pwd)
		g_sh->pipe_exit = 1;
	printf("%s\n", pwd);
}
