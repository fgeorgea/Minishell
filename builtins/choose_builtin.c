/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgea <fgeorgea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:47:02 by fgeorgea          #+#    #+#             */
/*   Updated: 2023/05/07 18:59:57 by fgeorgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(char *cmd, char **arg)
{
    int is_builtin;

    is_builtin = 1;
    if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
        ft_cd(arg[1]);
    else if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
        ft_echo(&arg[1]);
    else if (ft_strncmp(cmd, "env", 4) == 0 && ft_strlen(cmd) == 4)
        ft_env();
    else if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
        ft_exit_builtin();
    else if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
        ft_unset(&arg[1]);
    else if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
        ft_pwd();
    else if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
        ft_export(&arg[1]);
    else
        is_builtin -= 1;
    return (is_builtin);
}