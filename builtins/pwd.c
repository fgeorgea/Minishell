/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:17:30 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/24 15:12:20 by fgeorgea         ###   ########.fr       */
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
		ft_printf("%s\n", pwd);
		return ;
	}
	pwd = get_env_value("PWD");
	if (!pwd)
		set_exit(1);
	ft_printf("%s\n", pwd);
}
