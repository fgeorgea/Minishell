/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:17:30 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/06/08 01:14:56 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Prints the current working directory
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
