/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:17:30 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/28 18:58:37 by fgeorgea         ###   ########.fr       */
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
		ft_free((void **)&pwd);
		return ;
	}
	pwd = get_env_value("PWD");
	if (!pwd)
	{
		ft_putstr_fd("Minishell: pwd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories\n", 2);
		set_exit(1);
	}
	else
		printf("%s\n", pwd);
}
